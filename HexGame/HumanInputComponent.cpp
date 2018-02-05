#include "HumanInputComponent.h"
#include "Player.h"

#include <SDL.h>


HumanInputComponent::~HumanInputComponent() {
}

void HumanInputComponent::Update(Player& player) {
	SDL_Event an_event;
	if (SDL_PollEvent(&an_event)) {
		keyDown = keyUp = 0;
		switch (an_event.type) {
		case SDL_QUIT:
			// player->QuitGame();
			break;
		case SDL_KEYDOWN:
			ctrlPressed = ((an_event.key.keysym.mod & KMOD_CTRL) == KMOD_CTRL);
			shiftPressed = ((an_event.key.keysym.mod & KMOD_SHIFT) == KMOD_SHIFT);
			altPressed = ((an_event.key.keysym.mod & KMOD_ALT) == KMOD_ALT);
			keyDown = an_event.key.keysym.sym;
			//gameover = ((keyDown & SDLK_ESCAPE) == SDLK_ESCAPE);
			//OnKeyPressed();

			break;
		case SDL_KEYUP:
			ctrlPressed = ((an_event.key.keysym.mod & KMOD_CTRL) == KMOD_CTRL);
			shiftPressed = ((an_event.key.keysym.mod & KMOD_SHIFT) == KMOD_SHIFT);
			altPressed = ((an_event.key.keysym.mod & KMOD_ALT) == KMOD_ALT);
			keyUp = an_event.key.keysym.sym;
			//OnKeyReleased();
			break;
		case SDL_MOUSEMOTION:
			pmouseX = mouseX;
			pmouseY = mouseY;
			mouseX = an_event.motion.x;
			mouseY = an_event.motion.y;
			//OnMouseMoved();
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButton = an_event.button.button; // SDL_BUTTON_LEFT)
			mouseX = an_event.button.x;
			mouseY = an_event.button.y;
			//OnMousePressed();
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButton = an_event.button.button; // SDL_BUTTON_LEFT)
			mouseX = an_event.button.x;
			mouseY = an_event.button.y;
			//OnMouseReleased();
			break;
		default:
			// An event that we do not need to process
			break;

		}
	}
}
