# cinterface

[![Link to Mastodon profile](https://img.shields.io/badge/Version-1.0.0-blue?style=for-the-badge)](https://github.com/NikitaFoxze/cinterface)

Controller interface - этот файл предназначен облегчить манипуляции с интерфейсами в SA-MP. Он написан на основе кода mdialog от ziggi.

# Функции
### Показать интерфейс
```Pawn
Interface_Show(playerid, const function[])
```

### Закрыть интерфейс
```Pawn
Interface_Close(playerid, const function[])
```

### Закрыть интерфейс с аргументом hide
```Pawn
Interface_Closing(playerid, const function[], bool:hide)
```

### Узнать, открыт ли интрефейс
```Pawn
Interface_IsOpen(playerid, const function[] = "")
```

# Использование
```Pawn
InterfaceCreate:Inventory(playerid)
{
	ShowTDInventory(playerid);
	// Следующая логика...
	return 1;
}

InterfaceClose:Inventory(playerid)
{
	DestroyTDInventory(playerid);
	// Следующая логика...
	return 1;
}

InterfacePlayerClick:Inventory(playerid, PlayerText:playertextid)
{
	if(playertextid == TD_Inventory[playerid][0]) {

	}
	// Следующая логика...
	return 1;
}

InterfaceClick:Inventory(playerid, text:clickedid)
{
	if(_:clickedid == INVALID_TEXT_DRAW) {
		SelectTextDraw(playerid, 0xFFFFFFFF);
	}
	// Следующая логика...
	return 1;
}
```


