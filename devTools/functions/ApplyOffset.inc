

stock DT_ApplyOffset(&Float:x, &Float:y, &Float:z, Float:ang, Float:xOffset = 0.0, Float:yOffset = 0.0, Float:zOffset = 0.0) {

	ang = 360 - ang;

	x = (floatsin(ang, degrees) * yOffset + floatcos(ang, degrees) * xOffset + x);
	y = (floatcos(ang, degrees) * yOffset - floatsin(ang, degrees) * xOffset + y);

	z += zOffset;
}