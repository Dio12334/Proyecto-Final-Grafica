#include "../include/MeshComponent.h"
#include "../include/Shader.h"
#include "../include/Mesh.h"
#include "../include/Entity.h"
#include "../include/Game.h"
#include "../include/Renderer.h"
#include "../include/Texture.h"
#include "../include/VertexArray.h"

MeshComponent::MeshComponent(class Entity* owner):
	Component(owner),
	_mesh(nullptr),
	_textureIndex(0),
	_visible(true)
{
	_owner->getGame()->getRenderer()->addMeshComp(this);
}

MeshComponent::~MeshComponent(){
	_owner->getGame()->getRenderer()->removeMeshComp(this);
}

void MeshComponent::draw(class Shader *shader){
	if(_mesh){
		shader->setMatrixUniform("uWorldTransform", _owner->getWorldTransform());
		shader->setFloatUniform("uSpecPower", _mesh->getSpecPower());
		Texture* t = _mesh->getTexture(_textureIndex);
		if(t){
			t->setActive();
		}
		VertexArray* va = _mesh->getVertexArray();
		va->setActive();
		/* glDrawArrays(GL_POINTS, 0, va->getNumVerts()); */
		glDrawElements(GL_TRIANGLES, va->getNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

TunnelMeshComponent::TunnelMeshComponent(class Entity* owner): MeshComponent(owner){
	
}

TunnelMeshComponent::~TunnelMeshComponent(){

}

void TunnelMeshComponent::draw(class Shader *shader){
	if(_vertexArray){
		shader->setMatrixUniform("uWorldTransform", _owner->getWorldTransform());
		shader->setFloatUniform("uSpecPower", _mesh->getSpecPower());
		Texture* t = _mesh->getTexture(_textureIndex);
		if(t){
			t->setActive();
		}
		_vertexArray->setActive();
		/* glDrawArrays(GL_POINTS, 0, _vertexArray->getNumVerts()); */
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glDrawElements(GL_TRIANGLES, (int) _vertexArray->getNumIndices(), GL_UNSIGNED_INT, nullptr);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
}
