#include "../headers/SettingsValues.h"

int SettingsValues::getLanguage()
{
	return nLanguage;
}

int SettingsValues::getSkin()
{
	return nSkin;
}

int SettingsValues::getWidth()
{
	return nWidth;
}

int SettingsValues::getHeight()
{
	return nHeight;
}

float SettingsValues::getSettingTitle()
{
	return fSettingTitle;
}

float SettingsValues::getTitle()
{
	return fTitle;
}

bool SettingsValues::getFullscreen()
{
	return bFullscreen;
}


void SettingsValues::setLanguage(int nValue)
{
	nLanguage = nValue;
}

void SettingsValues::setSkin(int nValue)
{
	nSkin = nValue;
}

void SettingsValues::setWidth(int nValue)
{
	nWidth = nValue;
}

void SettingsValues::setHeight(int nValue)
{
	nHeight = nValue;
}

void SettingsValues::setSettingTitle(float fValue)
{
	fSettingTitle = fValue;
}

void SettingsValues::setTitle(float fValue)
{
	fTitle = fValue;
}

void SettingsValues::setFullscreen(bool bValue)
{
	bFullscreen = bValue;
}

void SettingsValues::setLanguageValues(int nLanguage, float fSettingtitle, float fTitle)
{
	setLanguage(nLanguage);
	setSettingTitle(fSettingtitle);
	setTitle(fTitle);
}

void SettingsValues::setScreenValues(int nWidth, int nHeight, bool bFullscreen)
{
	setWidth(nWidth);
	setHeight(nHeight);
	setFullscreen(bFullscreen);
}