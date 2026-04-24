

stock DT_RenameCommandList(commandArray[][][], totalCommands, start = 0) {
    new DT_string[DT_COMMAND_MAX_LENGTH + 16];
    
    for(new i = start; i < totalCommands; i++) {
        if(PC_CommandExists(commandArray[i][0]) == 1) {
            strins(commandArray[i][0], ""DT_RED_COLOR_TAG"dt"DT_MAIN_COLOR_TAG"", 0, sizeof(DT_string));
        }
        else {
            format(DT_string, sizeof(DT_string), "dt%s", commandArray[i][0]);
            PC_RenameCommand(DT_string, commandArray[i][0]);
        }
    }

	return 1;
}