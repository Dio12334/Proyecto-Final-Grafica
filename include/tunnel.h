#ifndef TUNNEL_H
#define TUNNEL_H

#include <cmath>
#include <random>
#include <iostream>
#include "VectorTem.h"

using namespace Math;
std::random_device rd;
std::default_random_engine dre(rd());

int RandomInt(int a, int b){
	std::uniform_int_distribution<int> dis(a, b);
	return dis(dre);
}

float RandomFloat(float a, float b){
	std::uniform_real_distribution<float> dis(a, b);
	return dis(dre);
}

#define BRANCHING_NUM 2


struct TunnelSegment{
	
	float radius;
	float length;
	Vector<float> direction;
	Vector<float> beginPosition;

	TunnelSegment* prev = nullptr;
	TunnelSegment* next[BRANCHING_NUM] = {nullptr};
};

static int val = 0;

TunnelSegment* CreateTunnel(TunnelSegment* father = nullptr){
	++val;
	TunnelSegment* seg = new TunnelSegment();
	seg->radius = RandomFloat(2, 5);
	seg->length = RandomFloat(10, 20);

	if(father){
		seg->prev = father;
		seg->direction = Vector<float>(RandomFloat(0, father->direction.x), RandomFloat(0, father->direction.y), RandomFloat(0, father->direction.z));
		seg->direction.normalize();
		seg->beginPosition = father->direction*father->length + father->beginPosition; 
	}
	else{
		seg->beginPosition = Vector<float>(0,0,0);
		seg->direction = Vector<float>(RandomFloat(-1, 1), RandomFloat(-1, 1), RandomFloat(-1, 1));
		seg->direction.normalize();
	}

	for(int i = 0; i < RandomInt(0, BRANCHING_NUM); ++i){
		seg->next[i] = CreateTunnel(seg);	
	}

	return seg;
}

int GetTunnelPoints(std::vector<float>& points, TunnelSegment* tun){
	
	auto perp = crossProduct(tun->direction, Vector<float>(0,1,0));
	perp.normalize();
	
	auto perp2 = crossProduct(perp, tun->direction);
	perp2.normalize();
	int numPoints = 0;
	int step = 5;
	int stepLength = tun->length/10;
	for(int j = 0; j < tun->length; j += stepLength){
		auto stepPos = tun->beginPosition + tun->direction*j;
		for(int i = 0; i < 360; i+=step){
			auto newPosition = stepPos + tun->radius*std::cos(toRadians((float)i))*perp + tun->radius*std::sin(toRadians((float)i))*perp2;	
			auto newNormal = std::cos(toRadians((float)i))*perp + std::sin(toRadians((float)i))*perp2;
			points.push_back(newPosition.x);
			points.push_back(newPosition.y);
			points.push_back(newPosition.z);
			points.push_back(newNormal.x);
			points.push_back(newNormal.y);
			points.push_back(newNormal.z);	
			points.push_back(1);
			points.push_back(1);
			++numPoints;
		}
	}
	return numPoints;
}

void GeneratePoints(TunnelSegment* tunnel, std::vector<float>& result, std::vector<int>& numberOfPoints){
	
	numberOfPoints.push_back(GetTunnelPoints(result, tunnel));
	for(int i = 0; i < BRANCHING_NUM; ++i){
		if(!tunnel->next[i])
			break;
		GeneratePoints( tunnel->next[i], result, numberOfPoints);

	}
}

std::vector<float> GenerateTunnel(std::vector<int>& numberOfPointsPerCylinder){
	TunnelSegment* tunnel = CreateTunnel();
	std::vector<float> result;
	GeneratePoints(tunnel, result, numberOfPointsPerCylinder);
	std::cout << val << std::endl;
	return result;
}

std::vector<unsigned int> GenerateIndices(const std::vector<float>& points, const std::vector<int>& pointsPerCylinder){
	std::vector<unsigned int> indices;
	/* std::cout << "Points per Cylinder:\n"; */
	/* for(size_t i = 0; i < pointsPerCylinder.size(); ++i) */
	/* 	std::cout << pointsPerCylinder[i] << std::endl; */
	
	size_t indexBeg = 0, indexEnd;
	for(size_t i = 0; i < pointsPerCylinder.size(); ++i){
		indexEnd = indexBeg + pointsPerCylinder[i];
		for(size_t j = indexBeg; j < indexEnd - 72; ++j){
			indices.push_back(j);
			if((j + 1) % 72 != 0 )
				indices.push_back(j + 1);
			else 
				indices.push_back(j - 71);
			indices.push_back(j + 72);
		}
		indexBeg = indexEnd;
	}

	return indices;
}

#endif
