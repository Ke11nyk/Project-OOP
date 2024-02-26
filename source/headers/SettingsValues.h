#pragma once

/**
* \brief This is the struct to save settings values
*/
struct SettingsValues
{
private:
    int nLanguage = 0; ///< Language of the game
    int nSkin = 0; ///< Skin of the player
    int nWidth = 1920; ///< Width of the window
    int nHeight = 1080; ///< Height of the window
    float fSettingTitle = 573; ///< X-position of the settings title
    float fTitle = 469.5; ///< X-position of the main title
    bool bFullscreen = 0; ///< State of the window

public:
    int getLanguage();
    int getSkin();
    int getWidth();
    int getHeight();
    float getSettingTitle();
    float getTitle();
    bool getFullscreen();

    void setLanguage(int nValue);
    void setSkin(int nValue);
    void setWidth(int nValue);
    void setHeight(int nValue);
    void setSettingTitle(float fValue);
    void setTitle(float fValue);
    void setFullscreen(bool bValue);
    void setLanguageValues(int nLanguage, float fSettingtitle, float fTitle);
    void setScreenValues(int nWidth, int nHeight, bool bFullscreen);
};