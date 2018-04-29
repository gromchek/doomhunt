#include "GameState_MainMenu.h"
#include "Render.h"
#include "MainMenu.h"
#include "TextureManager.h"

const sf::Color MENU_ITEM_SELECTED{ 244, 232, 0 };
const sf::Color MENU_ITEM{ 238, 66, 62 };


void GameState_MainMenu::Init()
{
	const auto &size = render.GetSize();

	renderView.camera.reset( { 0.0f, 0.0f, float( size.x ), float( size.y ) } );
	renderView.camera.setViewport( { 0.1f, 0.125f, 0.75f, 0.75f } );

    renderView.clearColor = DEFAULT_CLEAR_COLOR;

	menu.Init();

	gamelogo.setTexture( texManager.GetTextureByName( "gamelogo" ) );
	gamelogo.setPosition( { 0.0f, 0.0f } );
	gamelogo.scale( { 1.5f, 1.5f } );
	gamelogo.move( gamelogo.getLocalBounds().width / 2.0f, 0.0f );
}

void GameState_MainMenu::HandleEvents()
{
	menu.KeyInput();
}

void GameState_MainMenu::Draw()
{
	render.Draw( gamelogo );

	const auto &items = menu.GetItems();

	float indent = 0.0f;
	sf::Text text;

	const float xOffset = gamelogo.getPosition().x + gamelogo.getLocalBounds().width / 4.0f;

	const auto &camera = GetRenderView().camera;

	for( const auto item : items )
	{
		text.setString( item->GetName() );
		text.setCharacterSize( 64 );
		text.setPosition( { 0.0f, indent } );

		sf::Color color = ( item->isSelected() ? MENU_ITEM_SELECTED : MENU_ITEM );
		text.setFillColor( color );


		text.move( xOffset, camera.getSize().y / 2.0f + indent );

		render.DrawText( text );

		indent += 64.0f;
	}
}
