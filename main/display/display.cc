#include "emote_display.h"
#include <esp_log.h>
#include <cstring>
#include "lvgl.h"

#define TAG "EmoteDisplay"

// Định nghĩa màu xanh Cyan / Aqua đặc trưng của Pika (#2CE2E6)
#define COLOR_PIKA_CYAN lv_color_hex(0x2CE2E6)

EmoteDisplay::EmoteDisplay() {
    InitPikaUI();
}

EmoteDisplay::~EmoteDisplay() {
    if (container_ != nullptr) {
        lv_obj_del(container_);
    }
}

void EmoteDisplay::InitPikaUI() {
    // 1. Tạo container nền đen phủ kín màn hình
    container_ = lv_obj_create(lv_scr_act());
    lv_obj_set_size(container_, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_color(container_, lv_color_black(), 0);
    lv_obj_set_style_border_width(container_, 0, 0);
    lv_obj_set_style_pad_all(container_, 0, 0);
    lv_obj_center(container_);

    // 2. Tạo style dùng chung cho các đường vẽ (nét dày, bo tròn 2 đầu)
    lv_style_init(&style_line_);
    lv_style_set_arc_color(&style_line_, COLOR_PIKA_CYAN);
    lv_style_set_arc_width(&style_line_, 6);         // Độ dày nét vẽ (tùy chỉnh nếu màn hình nhỏ/lớn)
    lv_style_set_arc_rounded(&style_line_, true);     // Bo tròn 2 đầu nét vẽ

    // 3. Mắt trái (Dùng lv_arc)
    eye_left_ = lv_arc_create(container_);
    lv_obj_add_style(eye_left_, &style_line_, 0);
    lv_obj_set_size(eye_left_, 70, 70);
    lv_obj_align(eye_left_, LV_ALIGN_CENTER, -45, -10);
    lv_arc_set_bg_angles(eye_left_, 0, 0); // Ẩn đường viền nền của arc

    // 4. Mắt phải
    eye_right_ = lv_arc_create(container_);
    lv_obj_add_style(eye_right_, &style_line_, 0);
    lv_obj_set_size(eye_right_, 70, 70);
    lv_obj_align(eye_right_, LV_ALIGN_CENTER, 45, -10);
    lv_arc_set_bg_angles(eye_right_, 0, 0);

    // 5. Lông mày trái
    eyebrow_left_ = lv_arc_create(container_);
    lv_obj_add_style(eyebrow_left_, &style_line_, 0);
    lv_obj_set_size(eyebrow_left_, 45, 25);
    lv_obj_align(eyebrow_left_, LV_ALIGN_CENTER, -45, -50);
    lv_arc_set_bg_angles(eyebrow_left_, 0, 0);

    // 6. Lông mày phải
    eyebrow_right_ = lv_arc_create(container_);
    lv_obj_add_style(eyebrow_right_, &style_line_, 0);
    lv_obj_set_size(eyebrow_right_, 45, 25);
    lv_obj_align(eyebrow_right_, LV_ALIGN_CENTER, 45, -50);
    lv_arc_set_bg_angles(eyebrow_right_, 0, 0);

    // 7. Miệng
    mouth_ = lv_arc_create(container_);
    lv_obj_add_style(mouth_, &style_line_, 0);
    lv_obj_set_size(mouth_, 50, 35);
    lv_obj_align(mouth_, LV_ALIGN_CENTER, 0, 35);
    lv_arc_set_bg_angles(mouth_, 0, 0);

    // Thiết lập biểu cảm mặc định ban đầu
    SetEmotion("happy");
}

void EmoteDisplay::SetEmotion(const char* emotion) {
    if (emotion == nullptr) return;
    ESP_LOGI(TAG, "Changing emotion to Pika style: %s", emotion);

    if (strcmp(emotion, "happy") == 0 || strcmp(emotion, "smile") == 0 || strcmp(emotion, "listening") == 0) {
        // Biểu cảm vui tươi giống Pika (Mắt cong hình vầng trăng khuyết)[cite: 2]
        lv_arc_set_angles(eye_left_, 200, 340);
        lv_arc_set_angles(eye_right_, 200, 340);

        lv_arc_set_angles(eyebrow_left_, 210, 330);
        lv_arc_set_angles(eyebrow_right_, 210, 330);

        // Miệng uốn cong cười
        lv_arc_set_angles(mouth_, 30, 150);
    } 
    else if (strcmp(emotion, "sad") == 0) {
        // Biểu cảm buồn (Mắt & miệng úp ngược xuống)
        lv_arc_set_angles(eye_left_, 20, 160);
        lv_arc_set_angles(eye_right_, 20, 160);

        lv_arc_set_angles(eyebrow_left_, 30, 150);
        lv_arc_set_angles(eyebrow_right_, 30, 150);

        lv_arc_set_angles(mouth_, 210, 330);
    } 
    else if (strcmp(emotion, "thinking") == 0 || strcmp(emotion, "speaking") == 0) {
        // Trạng thái đang suy nghĩ / phát biểu (Mắt tròn xoe)
        lv_arc_set_angles(eye_left_, 0, 360);
        lv_arc_set_angles(eye_right_, 0, 360);

        lv_arc_set_angles(eyebrow_left_, 200, 340);
        lv_arc_set_angles(eyebrow_right_, 200, 340);

        lv_arc_set_angles(mouth_, 40, 140);
    } 
    else { 
        // Trạng thái bình thường (Neutral)
        lv_arc_set_angles(eye_left_, 180, 360);
        lv_arc_set_angles(eye_right_, 180, 360);

        lv_arc_set_angles(eyebrow_left_, 210, 330);
        lv_arc_set_angles(eyebrow_right_, 210, 330);

        lv_arc_set_angles(mouth_, 40, 140);
    }
}