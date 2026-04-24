

stock DT_SendHint(playerid, const message[]) {
    new DT_message[145];
    format(DT_message, sizeof(DT_message), ""DT_TAG_HINT"%s: %s", DT_TEXT_USE, message);

    return SendClientMessage(playerid, DT_COLOR_MAIN, DT_message);
}


stock DT_SendError(playerid, const message[]) {
    new DT_message[145];
    format(DT_message, sizeof(DT_message), ""DT_TAG_ERROR"%s", message);

    return SendClientMessage(playerid, DT_COLOR_MAIN, DT_message);
}


stock DT_SendSucc(playerid, const message[]) {
    new DT_message[145];
    format(DT_message, sizeof(DT_message), ""DT_TAG_HINT"%s", message);

    return SendClientMessage(playerid, DT_COLOR_MAIN, DT_message);
}
