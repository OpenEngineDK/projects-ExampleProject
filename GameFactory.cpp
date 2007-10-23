// Game Factory for an example project.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// Class header
#include "GameFactory.h"

// OpenEngine library
#include <Display/Viewport.h>
#include <Display/ViewingVolume.h>
#include <Display/SDLFrame.h>
#include <Devices/SDLInput.h>
#include <Renderers/OpenGL/Renderer.h>
#include <Renderers/OpenGL/RenderingView.h>
#include <Scene/SceneNode.h>
#include <Utils/Statistics.h>

// Example extension
#include <Hello/World.h>

// Project files
// ...

// Additional namespaces (others are in the header).
using namespace OpenEngine::Devices;
using namespace OpenEngine::Renderers::OpenGL;

/**
 * Game quit handler.
 *
 * This is an example of a keyboard listener.
 * Every time the a key is released a key (UP) event is sent to the
 * handle method. If the key symbol is escape it quits the game.
 *
 * Note that this will not work before you have implemented the
 * keyboard and mouse interfaces in SDLInput.
 *
 * The code to register the handler is found in the
 * GameFactory::SetupEngine method.
 */
class QuitEventHandler {
public:
    void HandleQuit(KeyboardEventArg arg) {
        if (arg.sym == KEY_ESCAPE) {
            OpenEngine::Hello::World();
            IGameEngine::Instance().Stop();
        }
    }
};

/**
 * Factory constructor.
 *
 * Initializes the different components so they are accessible when
 * the setup method is executed.
 */
GameFactory::GameFactory() {

    // Create a frame and viewport.
    this->frame = new SDLFrame(800, 600, 32);

    // Main viewport
    Viewport* viewport = new Viewport(*frame);

    // Bind the camera to the viewport
    viewport->SetViewingVolume(new ViewingVolume());

    // Create a renderer.
    this->renderer = new Renderer();

    // Add a rendering view to the renderer
    this->renderer->AddRenderingView(new RenderingView(*viewport));

}

/**
 * Setup handler.
 *
 * This is the main setup method of the game factory. Here you can add
 * any non-standard modules and perform other setup tasks prior to the
 * engine start up.
 *
 * @param engine The game engine instance.
 */
bool GameFactory::SetupEngine(IGameEngine& engine) {

    // Add your mouse and keyboard module here
    SDLInput* input = new SDLInput();
    engine.AddModule(*input);

    // Create a root scene node
    SceneNode* scene = new SceneNode();

    // Supply the scene to the renderer
    this->renderer->SetSceneRoot(scene);

    // Bind the quit handler (the keyboard module needs to work for
    // the handler to actually quit).
    // For more information on the event system please read:
    // http://openengine.dk/wiki/EventSystemGuide
    QuitEventHandler* quit_h = new QuitEventHandler();
    Listener<QuitEventHandler, KeyboardEventArg>* quit_l
        = new Listener<QuitEventHandler, KeyboardEventArg> (*quit_h, &QuitEventHandler::HandleQuit);
    IKeyboard::keyUpEvent.Add(quit_l);

    // Add some module
    engine.AddModule(*(new OpenEngine::Utils::Statistics(1000)));

    // Return true to signal success.
    return true;

}

// Other factory methods. The returned objects are all created in the
// factory constructor.
IFrame*      GameFactory::GetFrame()    { return this->frame;    }
IRenderer*   GameFactory::GetRenderer() { return this->renderer; }
