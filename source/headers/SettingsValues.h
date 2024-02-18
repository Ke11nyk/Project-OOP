#pragma once
struct SettingsValues
{
private:
    int nLanguage = 0;
    int nSkin = 0;
    int nWidth = 1920;
    int nHeight = 1080;
    float fSettingTitle = 573;
    float fTitle = 469.5;
    bool bFullscreen = 0;

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