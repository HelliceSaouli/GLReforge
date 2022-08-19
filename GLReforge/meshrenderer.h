#pragma once
#include "component.h"

#include "material.h"
#include "mesh.h"

#include "lightsource.h"
#include "pointlight.h"

#include "camera.h"

#include <vector>

class meshrenderer :public component
{
	public:
		meshrenderer(mesh* _entity_mesh, material* _mesh_material, std::vector<lightsource*> _lights, camera* _cam);
		~meshrenderer();
	
	public:
		void render() override;

	private:
		material* mesh_material;
		mesh* entity_mesh;
		std::vector<lightsource*> lights;
		camera* cam;

};

