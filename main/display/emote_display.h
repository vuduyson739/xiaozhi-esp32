#ifndef EMOTE_DISPLAY_H_
#define EMOTE_DISPLAY_H_

#include "display.h"
#include "lvgl.h"

class EmoteDisplay : public Display {
public:
    EmoteDisplay();
    ~EmoteDisplay() override;

    void SetEmotion(const char* emotion) override;

private:
    void InitPikaUI();

    lv_obj_t* container_ = nullptr;
    lv_obj_t* eye_left_ = nullptr;
    lv_obj_t* eye_right_ = nullptr;
    lv_obj_t* eyebrow_left_ = nullptr;
    lv_obj_t* eyebrow_right_ = nullptr;
    lv_obj_t* mouth_ = nullptr;
    lv_style_t style_line_;
};

#endif // EMOTE_DISPLAY_H_