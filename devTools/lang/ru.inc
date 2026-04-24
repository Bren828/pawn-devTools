#if defined _devTools_lang_included
	#endinput
#endif
#define _devTools_lang_included


new DT_DIALOG_MENU[] = 
	"Получить расстояние от точки \t %s\t\n\
	Телепорт по метке на карте \t %s\n\
	Получить индекс анимации \t %s\n\
	Отключить функции Kick/Ban \t %s\n\
	Режим бога (GodMode) \t %s\n\
	Camera target \t %s\n\
	Двойной прыжок \t %s\n\
	Мега пуля \t %s\n\
	{6fa8dc}Public log\n\
	Статистика игрока \t %s\n\
	Статистика транспорта \t %s\n\
	{366c90}Rak{f69d1d}Net: {FFFFFF}Статистика игрока \t %s\n\
	{366c90}Rak{f69d1d}Net: {FFFFFF}Статистика транспорта \t %s\n\
	{366c90}Rak{f69d1d}Net: {FFFFFF}Статистика пассажиров транспорта \t %s";


new DT_DIALOG_PUBLICS[] = 
	"Key State Change \t %s\n\
	Take Damage \t %s\n\
	Give Damage \t %s\n\
	Weapon Shot \t %s\n\
	Death \t %s\n\
	Spawn \t %s\n\
	State Change \t %s\n\
	Enter Vehicle \t %s\n\
	Exit Vehicle \t %s";


new 
	DT_SELECT_BUTTON[] = 				"Выбрать",
	DT_CLOSE_BUTTON[] = 				"Закрыть",
	DT_BACK_BUTTON[] = 					"Назад",
	DT_TEXT_INVALID[] = 				"Неверный ID";


#if defined DT_ENABLE_IGNORE_PUNISHMENTS
	new 
		DT_TEXT_IGNORING_PUNISHMENT[] = "The '%s' attempt was ignored.";
#else
	new 
		DT_TEXT_IGNORING_PUNISHMENT[] = "Включите '#define DT_ENABLE_IGNORE_PUNISHMENTS' для использование этой функции";
#endif


//Dialog
	new 
		DT_DIALOG_PLAYER_STATS_HEADER[] = 	"Статистика игрока",
		DT_DIALOG_PLAYER_STATS[] = 			"{FFFFFF}Введите ID игрока:",

		DT_DIALOG_VEHICLE_STATS_HEADER[] = 	"Статистика транспорта",
		DT_DIALOG_VEHICLE_STATS[] = 		"{FFFFFF}Введите ID транспорта:";


#if !defined PAWNRAKNET_INC_
	new 
		DT_TEXT_NO_RAKNET_PLUGIN[] = "Подключите плагин 'PawnRaknet by katursis' для работы этой функции.";
#endif


#if !defined DT_DISABLE_COMMANDS

	new DT_DIALOG_COMMANDS[] =
		"Команды игрока\n\
		Команды транспорта\n\
		Команды по объектам";

	new 
		DT_NEXT_BUTTON[] = 		"Дальше",
		DT_CONFIRM_BUTTON[] = 	"Да",
		DT_CANCEL_BUTTON[] = 	"Нет",
		DT_LIST_COMMANDST[] = 	"Список команд";


// Player
	new DT_PLAYER_COMMANDS[DT_MAX_PLAYER_COMMANDS][2][DT_COMMAND_DESC_LENGTH] = {
		{"dt",					"Dev Tools меню"},
		{"dtpublic",			"Меню вызова пабликов"},
		{"gotopos",				"Телепортироваться по позициям X Y Z"},
		{"goto",				"Телепортироваться к игроку"},
		{"gethere",				"Телепортировать игрока к себе"},
		{"setint",				"Изменить интерьер"},
		{"setworld",			"Изменить виртуальный мир"},
		{"spawn",				"Заспавнить игрока"},
		{"sethp",				"Установить здоровье игроку"},
		{"setar",				"Установить броню для игроку"},
		{"giveweapon",			"Выдать оружие игроку"},
		{"givemoney",			"Выдать деньги игроку"},
		{"setscore",			"Установить счет игроку"},
		{"setskin",				"Установить скин игроку"},
		{"playsound",			"Воспроизвести звук"},
		{"playcrime",			"Воспроизвести звук преступления"},
		{"explosion",			"Создать взрыв"},
		{"settime",				"Изменить время"},
		{"setweather",			"Изменить погоду"},
		{"playanim",			"Воспроизвести анимацию"},
		{"getcam",				"Получить текущее положение камеры"},
		{"attedit",				"Создать прикрепленный объект"},
		{"setaction",			"Установить специальное действие"},
		{"startrecord",			"Начать запись бота"},
		{"stoprecord",			"Остановить запись бота"},
		{"fstyle",				"Установить стиль боя"},
		{"setdrunk",			"Установить уровень опьянения"},
		{"weaponskill",			"Установить уровень владения оружием"},
		{"setwanted",			"Установить уровень розыска"},
		{"cursor",				"Показать курсор"}
	};


// Vehicle
	new DT_VEHICLE_COMMANDS[DT_MAX_VEHICLE_COMMANDS][2][DT_COMMAND_DESC_LENGTH] = {	
		{"veh",					"Создать автомобиль"},
		{"delveh",				"Удалить автомобиль"},
		{"repairveh",			"Ремонт автомобиля"},
		{"setvehhp",			"Установить здоровье автомобиля"},
		{"gotoveh",				"Телепортироваться к транспорту"},
		{"gethereveh",			"Телепортировать транспорт к себе"},
		{"setvehcolor",			"Изменить цвет транспорта"},
		{"setcomp",				"Установить компонент тюнинга"},
		{"remcomp",				"Снять компонент тюнинга"},
		{"vehen",				"Запустить/заглушить двигатель"},
		{"vehli",				"Включить/включить фары"},
		{"vehdo",				"Открыть/закрыть двери"}
	};


// object
	#if !defined DT_DISABLE_OBJECT_EDITOR
		new DT_OBJECT_COMMANDS[DT_MAX_OBJECT_COMMANDS][2][DT_COMMAND_DESC_LENGTH] = {
			{"loadmap",			"Загрузить карту"},
			{"savemap",			"Сохранить карту"},
			{"ocreate",			"Создать объект"},
			{"odel",			"Удалить объект"},
			{"odelall",			"Удалить все объекты"},
			{"oedit",			"Редактировать объект"},
			{"oselect", 		"Выбрать объект курсором"},
			{"ocopy",			"Копировать объект"},
			{"ogoto",			"Телепортироваться к объекту"},
			{"ogethere",		"Телепортировать объект к себе"},
			{"oinfo",			"Информация об объекте"},
			{"otextdis",		"Установить расстояние 3D текста"},
			{"otextdetal",		"Отобразить подробную информацию о объектах"},
			{"oworld", 			"Установить виртуальный мир объекту"},
			{"oworldall",		"Установить виртуальный мир всем объектам"},
			{"oint", 			"Установить интерьер объекту"},
			{"ointall", 		"Установить интерьер всем объектам"},
			{"odis", 			"Установить расстояние объекту"},
			{"odisall", 		"Установить расстояние всем объектам"},
			{"osetm", 			"Установить материал"},
			{"osetmt", 			"Установить текстовый материал"},
			{"ormt", 			"Удаляет материал"},
			{"ormtt", 			"Удалить текстовый материал"},
			{"ox", 				"Установить положение X"},
			{"oy", 				"Установить положение Y"},
			{"oz", 				"Установить положение Z"},
			{"orx", 			"Установить положение RX"},
			{"ory", 			"Установить положение RY"},
			{"orz",				"Установить положение RZ"},
			{"oxall", 			"Установить положение X всем объектам"},										
			{"oyall", 			"Установить положение Y всем объектам"},										
			{"ozall", 			"Установить положение Z всем объектам"}
		};
	#endif


//Other text
	new 
		DT_TEXT_USE[] = 					"Используйте",
		DT_TEXT_YOUR[] = 					"Ваш",
		DT_TEXT_INVALID_COLOR[] = 			"Неверный номер цвета (0 - 255)",
		DT_TEXT_INVALID_PAINTJOB[] = 		"Неверный номер окраски (0 - 3)",
		DT_TEXT_INVALID_MODEL[] = 			"Неверная модель",
		DT_TEXT_INVALID_WEAPON_ID[] = 		"Неверный номер оружия",
		DT_TEXT_INVALID_SKIN_ID[] = 		"Неверный номер скина",
		DT_TEXT_INVALID_LENGTH[] = 			"Длина от 2 до %d символов",
		DT_TEXT_NOT_FOUND[] = 				"Транспортное средство не найдено",
		DT_TEXT_FAILED_CREATE_VEHICLE[] = 	"Не удалось создать транспорт";


//Command text

	// Player
	new 
		DT_CMD_TEXT_GOTOPOS[] = 			"Телепорт | X: %.4f | Y: %.4f | Z: %.4f | World: %d | Interior: %d",
		DT_CMD_TEXT_GOTO[] = 				"Вы телепортированы к %s(%d)",
		DT_CMD_TEXT_GETHERE[] = 			"Вы телепортировали %s(%d) к себе",
		DT_CMD_TEXT_SETINT[] = 				"Новый интерьер: %d | Старый интерьер: %d",
		DT_CMD_TEXT_SETWORLD[] = 			"Новый виртуальный мир: %d | Старый виртуальный мир: %d",
		DT_CMD_TEXT_SPAWN[] = 				"Вы заспавнили игрока %s(%d)",
		DT_CMD_TEXT_SETHP[] = 				"Вы установили %.1f здоровье %s(%d)",
		DT_CMD_TEXT_SETAR[] = 				"Вы установили %.1f брони %s(%d)",
		DT_CMD_TEXT_GIVEWEAPON[] = 			"Вы выдали оружие %d с %d патронами %s(%d)",
		DT_CMD_TEXT_GIVEMONEY[] = 			"Вы выдали $%d игроку %s(%d)",
		DT_CMD_TEXT_SETSCORE[] = 			"Вы установили %d очков %s(%d)",
		DT_CMD_TEXT_SETSKIN[] = 			"Вы выдали скин %d игроку %s(%d)",
		DT_CMD_TEXT_PLAYSOUND[] = 			"Воспроизведен звук %d",
		DT_CMD_TEXT_EXPLOSION[] = 			"Создан взрыв %d для игрока %s(%d)",
		DT_CMD_TEXT_SETTIME[] = 			"Установлено время %d",
		DT_CMD_TEXT_SETWEATHER[] = 			"Установлена погода %d",
		DT_CMD_TEXT_SETACTION[] = 			"Установлено действие %d",
		DT_CMD_TEXT_STARTRECORD[] = 		"Вы начали запись бота",
		DT_CMD_TEXT_STOPRECORD[] = 			"Вы остановили запись бота. Файл был записан в папку 'scriptfiles'",
		DT_CMD_TEXT_FSTYLE[] = 				"Вы изменили стиль боя на %d",
		DT_CMD_TEXT_SETDRUNK[] = 			"Вы установили уровень опьянения на %d",
		DT_CMD_TEXT_ATTEDIT_INFO[] = 		"Редактирование объекта на игроке",
		DT_CMD_TEXT_ATTEDIT_CAPTION[] = 	"{FFFFFF}Продолжить редактирование предыдущего объекта?",
		DT_CMD_TEXT_WEAPONSKILL[] = 		"Вы установили уровень владения оружием %d на %d",
		DT_CMD_TEXT_SETWANTED[] = 			"Вы установили уровень розыска на %d",
		DT_CMD_TEXT_PLAYCRIME[] = 			"Воспроизведен звук преступления | Suspect: %d | Crime: %d";


	// Vehicle
	new 
		DT_CMD_TEXT_VEH[] = 				"Транспорт модели %d был создан",
		DT_CMD_TEXT_DELVEH[] = 				"Удалено транспорта %d шт",
		DT_CMD_TEXT_GOTOVEH[] = 			"Вы телепортированы к транспорту ID: %d",
		DT_CMD_TEXT_GETHEREVEH[] =			"Вы телепортировали транспорт ID: %d к себе",
		DT_CMD_TEXT_REPAIRVEH[] = 			"Транспорт отремонтирован",
		DT_CMD_TEXT_SETVEHHP[] =  			"Вы установили %.1f здоровья транспорту",
		DT_CMD_TEXT_SETVEHCOLOR[] = 		"Вы изменили цвет транспорта | Color 1: %d | Color 2: %d | Paintjob: %d",
		DT_CMD_TEXT_SETCOMP[] = 			"Вы установили компонент %d",
		DT_CMD_TEXT_REMCOMP[] = 			"Вы удалили компонент %d",
		DT_CMD_TEXT_VEHEN_ON[] = 			"Вы завели двигатель",
		DT_CMD_TEXT_VEHEN2_OFF[] = 			"Вы выключили двигатель",
		DT_CMD_TEXT_VEHLI_ON[] = 			"Вы включили свет",
		DT_CMD_TEXT_VEHLI_OFF[] = 			"Вы выключили свет",
		DT_CMD_TEXT_VEHDO_CLOSED[] = 		"Вы закрыли двери",
		DT_CMD_TEXT_VEHDO_OPENED[] = 		"Вы открыли двери";


	// Object
	#if !defined DT_DISABLE_OBJECT_EDITOR
		new 
			DT_TEXT_OBJECT_NOT_CREATED[] = 		"Объект не создан",
			DT_TEXT_LIMIT_OBJECTS[] = 			"Достигнут предел создания объектов",
			DT_TEXT_PROJECT_NOT_FOUND[] = 		"Проект не найден",
			DT_TEXT_INVALID_FOLDER[] = 			"Создайте папку '"#DT_OBJECTS_FOLDER"' в каталоге 'scriptfiles'",
			DT_TEXT_INVALID_MATERIAL_INDEX[] = 	"Неверный индекс материала (0 - 15)",
			DT_TEXT_LOADING_MAP[] = 			"Проект '%s' был загружен с объектами %d шт",
			DT_TEXT_SAVING_MAP[] = 				"Проект '%s' с объектами %d шт был сохранен в папку scriptfiles\\"#DT_OBJECTS_FOLDER"",
			DT_TEXT_FAILED_CREATE_OBJECT[] = 	"Не удалось создать объект";

		#if !defined RemoveDynamicObjectMaterialText || !defined RemoveDynamicObjectMaterial
			new 
				DT_TEXT_OLD_VERSION_PLUGIN[] = "Для использования данной команды обновите плагин Streamer до версии v2.9.5 и выше.";
		#endif


		new 
			DT_CMD_TEXT_OCREATE[] = 			"Объект %d был создан под индексом %d",
			DT_CMD_TEXT_ODEL[] = 				"Объект под индексом %d удален",
			DT_CMD_TEXT_ODELALL[] = 			"Все %d шт объеков удалены",
			DT_CMD_TEXT_OCOPY[] = 				"Объект %d был скопирован в индекс %d",
			DT_CMD_TEXT_OGOTO[] = 				"Вы телепортировались к объекту под индексом %d",
			DT_CMD_TEXT_OGETHERE[] = 			"Объект индека %d был телепортирован к вам",
			DT_CMD_TEXT_OTEXTDIS[] = 			"Расстояние 3D текста изменено на %.1f",
			DT_CMD_TEXT_OTEXTDETAL_ON[] = 		"Подробная информация включена",
			DT_CMD_TEXT_OTEXTDETAL_OFF[] = 		"Подробная информация отключена",
			DT_CMD_TEXT_OWORLD[] = 				"Вы изменили виртуальный мир объекта на %d",
			DT_CMD_TEXT_OWORLDALL[] = 			"Вы изменили виртуальный мир на %d для всех объектов",
			DT_CMD_TEXT_OINT[] = 				"Вы изменили интерьер объекта на %d",
			DT_CMD_TEXT_OINTALL[] = 			"Вы изменили интерьер на %d для всех объектов",
			DT_CMD_TEXT_ODIS[] = 				"Вы установили расстояние объекта под индексом %d на %.2f",
			DT_CMD_TEXT_ODISALL[] = 			"Вы установили расстояние %.2f для всех объектов",
			DT_CMD_TEXT_OSETM[] = 				"Материал объекта под индексом %d изменен на %d, %d, %s, %s, %d",
			DT_CMD_TEXT_OSETM_TXD_LEN[] = 		"Длина 'Txd name' от 1 до 64 символов",
			DT_CMD_TEXT_OSETM_TEXTURE_LEN[] = 	"Длина 'Texture name' от 1 до 64 символов",
			DT_CMD_TEXT_OSETMT[] = 				"Текст объекта под индексом %d изменен на %d, %s, %d, %s, %d, %d, %d, %d, %d",
			DT_CMD_TEXT_OSETMT_TEXT_LEN[] = 	"Длина текста от 1 до 144 символов",
			DT_CMD_TEXT_OSETMT_FONT_LEN[] = 	"Длина 'FontFace' от 1 до 64 символов",
			DT_CMD_TEXT_ORMT[] = 				"У объекта под индексом %d был удален материал в слоте %d",
			DT_CMD_TEXT_ORMTT[] = 				"У объекта под индексом %d был удален текст в слоте %d",
			DT_CMD_TEXT_OX[] = 					"Позиция X объекта под индексом %d изменена с %f на %f",
			DT_CMD_TEXT_OY[] = 					"Позиция Y объекта под индексом %d изменена с %f на %f",
			DT_CMD_TEXT_OZ[] = 					"Позиция Z объекта под индексом %d изменена с %f на %f",
			DT_CMD_TEXT_ORX[] = 				"Позиция RX объекта под индексом %d изменена с %f на %f",
			DT_CMD_TEXT_ORY[] = 				"Позиция RY объекта под индексом %d изменена с %f на %f",
			DT_CMD_TEXT_ORZ[] = 				"Позиция RZ объекта под индексом %d изменена с %f на %f",
			DT_CMD_TEXT_OXALL[] = 				"Позиция X всех объектов изменена на %f",
			DT_CMD_TEXT_OYALL[] = 				"Позиция Y всех объектов изменена на %f",
			DT_CMD_TEXT_OZALL[] = 				"Позиция Z всех объектов изменена на %f";
	#endif
	

#endif