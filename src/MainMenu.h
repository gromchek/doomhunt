#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>
#include <vector>
#include <memory>

class MenuItem
{
private:
	std::string name;
	bool selected;

public:
	MenuItem() = delete;
	explicit MenuItem( const std::string &itemName );
	virtual ~MenuItem() = default;

	virtual void Action() = 0;

	void Select();
	void Unselect();
	bool isSelected() const;

	const std::string &GetName() const;
};

inline MenuItem::MenuItem( const std::string &itemName ) : name( itemName ), selected( false )
{
}

inline void MenuItem::Select()
{
	selected = true;
}

inline void MenuItem::Unselect()
{
	selected = false;
}

inline bool MenuItem::isSelected() const
{
	return selected;
}

inline const std::string &MenuItem::GetName() const
{
	return name;
}


class ItemNewGame final : public MenuItem
{
private:
public:
	ItemNewGame() = delete;
	explicit ItemNewGame( const std::string &itemName );
	virtual ~ItemNewGame() = default;

	virtual void Action() override;
};

inline ItemNewGame::ItemNewGame( const std::string &itemName ) : MenuItem( itemName )
{
}

class ItemViewscore final : public MenuItem
{
private:
public:
	ItemViewscore() = delete;
	explicit ItemViewscore( const std::string &itemName );
	virtual ~ItemViewscore() = default;

	virtual void Action() override;
};

inline ItemViewscore::ItemViewscore( const std::string &itemName ) : MenuItem( itemName )
{
}

class ItemQuitGame final : public MenuItem
{
private:
public:
	ItemQuitGame() = delete;
	explicit ItemQuitGame( const std::string &itemName );
	virtual ~ItemQuitGame() = default;

	virtual void Action() override;
};

inline ItemQuitGame::ItemQuitGame( const std::string &itemName ) : MenuItem( itemName )
{
}

using MenuItemPtr = std::shared_ptr<MenuItem>;

class MainMenu
{
private:
	std::vector<MenuItemPtr> items;
	unsigned int currentItem;

public:
	MainMenu() = default;
	~MainMenu() = default;

	void Init();

	void UpItem();
	void DownItem();

	const std::vector<MenuItemPtr> &GetItems() const;

	void KeyInput();
};

inline void MainMenu::UpItem()
{
	items[currentItem]->Unselect();

	currentItem -= 1;
	if( currentItem > items.size() )
	{
		currentItem = items.size() - 1;
	}

	items[currentItem]->Select();
}

inline void MainMenu::DownItem()
{
	items[currentItem]->Unselect();

	currentItem += 1;
	if( currentItem == items.size() )
	{
		currentItem = 0;
	}

	// currentItem %= items.size();

	items[currentItem]->Select();
}


#endif // MAINMENU_H
