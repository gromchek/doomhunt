#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Render.h"
#include "UserInput.h"
#include "Game.h"
#include "TextureManager.h"
#include "Rnd.h"


void Sys_ProcessEvents( sf::RenderWindow &win );

int main( /*int argc, char *argv[]*/ )
{
    auto displayMode = ( R_FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Close );
    sf::RenderWindow win( sf::VideoMode( R_WIDTH, R_HEIGHT ), "Doom hunt", displayMode );

    sf::Clock clock;

    win.setFramerateLimit( R_MAX_FPS );
    win.setKeyRepeatEnabled( false );
    win.setMouseCursorVisible( false );

    Rnd_Init();

    render.Init( win );

    texManager.Init();

    texManager.LoadTexture( "gamelogo" );
    texManager.LoadTexture( "pks", false );
    texManager.LoadTexture( "crosshair" );
    texManager.LoadTexture( "bg" );
    texManager.LoadTexture( "soulsheet", false );
    texManager.LoadTexture( "gameover", false );

    game.Init();

    game.thisTime = clock.getElapsedTime().asMilliseconds();

    while( !game.Closing() )
    {
        game.thisTime = clock.getElapsedTime().asMilliseconds();
        game.time = game.thisTime - game.oldTime;

        Sys_ProcessEvents( win );

        game.Update();

        auto state = game.states.CurrentState();

        render.Clear( state->GetRenderView().clearColor );
        render.SetRenderView( state->GetRenderView().camera );

        state->Draw();

        render.SwapBuffer();

        game.oldTime = game.thisTime;
    }

    win.close();

    game.scores.UpdateRecords();
    game.scores.WriteFile( scoreFile );

    return 0;
}


void Sys_ProcessEvents( sf::RenderWindow &win )
{
    userInput.ReleaseAllKey();

    sf::Event event;

    while( win.pollEvent( event ) )
    {
        if( event.type == sf::Event::Closed )
        {
            game.QuitGame();
            break;
        }

        switch( event.type )
        {
        case sf::Event::KeyPressed:
            userInput.SetKey( event.key.code, true );
            break;
        case sf::Event::KeyReleased:
            userInput.SetKey( event.key.code, false );
            break;
        case sf::Event::MouseButtonPressed:
            userInput.SetMouseKey( event.mouseButton.button, true );
            break;
        case sf::Event::MouseButtonReleased:
            userInput.SetMouseKey( event.mouseButton.button, false );
            break;

        default:
            break;
        }
    }

    auto m = sf::Mouse::getPosition( win );

    auto clampMouse = []( int &dim, const int dimMaxSize )
    {
        if( dim + 32 > dimMaxSize )
        {
            dim = dimMaxSize - 32;
        }

        if( dim - 32 <= 0 )
        {
            dim = 32;
        }
    };

    clampMouse( m.x, win.getSize().x );
    clampMouse( m.y, win.getSize().y );

    userInput.SetMousePosition( m.x, m.y );
}
