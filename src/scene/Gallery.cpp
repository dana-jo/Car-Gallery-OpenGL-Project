#include "scene/Gallery.h"
#include "../objects/Box.h"
#include "../graphics/Material.h"
#include "scene/GalleryShell.h"
#include "graphics/Texture.h"

Gallery::Gallery()
{

	float width = 120.0f;
	float depth = 120.0f;
	float height = 40.0f;
	float wallThickness = 0.3f;

    shell = new GalleryShell(width, depth, height, wallThickness);

	shell->position = { 0.0f, 0.0f, 0.0f };
	addChild(shell);
}

Gallery::~Gallery() = default;

