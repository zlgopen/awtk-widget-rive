#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/default/inc/strings/zh_CN.data"
#include "assets/default/inc/strings/en_US.data"
#include "assets/default/inc/styles/main.data"
#include "assets/default/inc/styles/keyboard.data"
#include "assets/default/inc/styles/default.data"
#include "assets/default/inc/ui/kb_ascii.data"
#include "assets/default/inc/ui/kb_phone.data"
#include "assets/default/inc/ui/main.data"
#include "assets/default/inc/ui/kb_int.data"
#include "assets/default/inc/ui/kb_hex.data"
#include "assets/default/inc/ui/kb_float.data"
#include "assets/default/inc/ui/kb_ufloat.data"
#include "assets/default/inc/ui/kb_default.data"
#include "assets/default/inc/ui/kb_uint.data"
#include "assets/default/inc/data/illustration_1_riv.data"
#include "assets/default/inc/data/heart_riv.data"
#include "assets/default/inc/data/love_note_4_riv.data"
#include "assets/default/inc/data/snowman2_riv.data"
#include "assets/default/inc/data/laptop_slide_riv.data"
#include "assets/default/inc/data/blink_simple_2_riv.data"
#include "assets/default/inc/data/headphones_riv.data"
#include "assets/default/inc/data/rocket_reload_riv.data"
#include "assets/default/inc/data/flux_capacitor2_riv.data"
#include "assets/default/inc/data/landing_riv.data"
#include "assets/default/inc/data/handshake_riv.data"
#include "assets/default/inc/data/notebook_demo2_riv.data"
#include "assets/default/inc/data/rudolph_riv.data"
#include "assets/default/inc/data/flag_riv.data"
#include "assets/default/inc/data/iron_giant2_riv.data"
#include "assets/default/inc/data/marker_riv.data"
#include "assets/default/inc/data/cute_cake_riv.data"
#include "assets/default/inc/data/diamond_riv.data"
#include "assets/default/inc/data/zombie_riv.data"
#include "assets/default/inc/data/working_as_a_team_riv.data"
#include "assets/default/inc/data/weather_icon_example_riv.data"
#include "assets/default/inc/data/mail_riv.data"
#include "assets/default/inc/data/space_camp_riv.data"
#include "assets/default/inc/data/bear_riv.data"
#include "assets/default/inc/data/stroke_reflection_effect_riv.data"
#include "assets/default/inc/data/tv_color_riv.data"
#include "assets/default/inc/data/question_icon_riv.data"
#include "assets/default/inc/data/beach_icon_riv.data"
#include "assets/default/inc/data/dory_riv.data"
#include "assets/default/inc/data/phone_drop_riv.data"
#include "assets/default/inc/data/juice063_riv.data"
#include "assets/default/inc/data/buggy_riv.data"
#include "assets/default/inc/data/neon_car_riv.data"
#include "assets/default/inc/data/search_riv.data"
#include "assets/default/inc/data/truck063_riv.data"
#include "assets/default/inc/data/notification_icon_3_riv.data"
#include "assets/default/inc/data/runtime_color_change_riv.data"
#include "assets/default/inc/data/poison_loader_riv.data"
#include "assets/default/inc/data/marty_v6_riv.data"
#include "assets/default/inc/data/flame_and_spark_riv.data"
#include "assets/default/inc/data/documents3_riv.data"
#include "assets/default/inc/data/teeny_tiny_file_riv.data"
#include "assets/default/inc/data/walkcycle_try_riv.data"
#include "assets/default/inc/data/calendar_icon2_riv.data"
#include "assets/default/inc/data/knight063_riv.data"
#include "assets/default/inc/data/barrier_riv.data"
#include "assets/default/inc/data/hig_five_icon_riv.data"
#include "assets/default/inc/data/space_reload_riv.data"
#include "assets/default/inc/data/planet_riv.data"
#include "assets/default/inc/data/laces_riv.data"
#include "assets/default/inc/data/marine_corps_running_riv.data"
#include "assets/default/inc/data/portable_table_riv.data"
#ifdef WITH_STB_IMAGE
#include "assets/default/inc/images/radio_unchecked_d.res"
#include "assets/default/inc/images/arrow_up_n.res"
#include "assets/default/inc/images/arrow_right_p.res"
#include "assets/default/inc/images/arrow_right_f.res"
#include "assets/default/inc/images/arrow_up_o.res"
#include "assets/default/inc/images/arrow_left_o.res"
#include "assets/default/inc/images/arrow_right_d.res"
#include "assets/default/inc/images/arrow_left_n.res"
#include "assets/default/inc/images/check_checked_d.res"
#include "assets/default/inc/images/radio_checked.res"
#include "assets/default/inc/images/check_unchecked_d.res"
#include "assets/default/inc/images/radio_checked_d.res"
#include "assets/default/inc/images/arrow_down_n.res"
#include "assets/default/inc/images/arrow_down_o.res"
#include "assets/default/inc/images/arrow_down_d.res"
#include "assets/default/inc/images/arrow_down_p.res"
#include "assets/default/inc/images/arrow_down_f.res"
#include "assets/default/inc/images/radio_unchecked.res"
#include "assets/default/inc/images/check_unchecked.res"
#include "assets/default/inc/images/arrow_up_p.res"
#include "assets/default/inc/images/arrow_right_n.res"
#include "assets/default/inc/images/arrow_right_o.res"
#include "assets/default/inc/images/arrow_up_f.res"
#include "assets/default/inc/images/arrow_left_d.res"
#include "assets/default/inc/images/arrow_left_f.res"
#include "assets/default/inc/images/arrow_up_d.res"
#include "assets/default/inc/images/arrow_left_p.res"
#include "assets/default/inc/images/check_checked.res"
#else
#endif /*WITH_STB_IMAGE*/
#ifdef WITH_VGCANVAS
#endif /*WITH_VGCANVAS*/
#ifdef WITH_TRUETYPE_FONT
#include "assets/default/inc/fonts/default.res"
#else /*WITH_TRUETYPE_FONT*/
#endif /*WITH_TRUETYPE_FONT*/
#endif /*WITH_FS_RES*/

ret_t assets_init(void) {
  assets_manager_t* am = assets_manager();
  assets_manager_set_theme(am, "default");

#ifdef WITH_FS_RES
  assets_manager_preload(am, ASSET_TYPE_FONT, "default");
  assets_manager_preload(am, ASSET_TYPE_STYLE, "default");
#else
  assets_manager_add(am, strings_zh_CN);
  assets_manager_add(am, strings_en_US);
  assets_manager_add(am, style_main);
  assets_manager_add(am, style_keyboard);
  assets_manager_add(am, style_default);
  assets_manager_add(am, ui_kb_ascii);
  assets_manager_add(am, ui_kb_phone);
  assets_manager_add(am, ui_main);
  assets_manager_add(am, ui_kb_int);
  assets_manager_add(am, ui_kb_hex);
  assets_manager_add(am, ui_kb_float);
  assets_manager_add(am, ui_kb_ufloat);
  assets_manager_add(am, ui_kb_default);
  assets_manager_add(am, ui_kb_uint);
  assets_manager_add(am, data_illustration_1_riv);
  assets_manager_add(am, data_heart_riv);
  assets_manager_add(am, data_love_note_4_riv);
  assets_manager_add(am, data_snowman2_riv);
  assets_manager_add(am, data_laptop_slide_riv);
  assets_manager_add(am, data_blink_simple_2_riv);
  assets_manager_add(am, data_headphones_riv);
  assets_manager_add(am, data_rocket_reload_riv);
  assets_manager_add(am, data_flux_capacitor2_riv);
  assets_manager_add(am, data_landing_riv);
  assets_manager_add(am, data_handshake_riv);
  assets_manager_add(am, data_notebook_demo2_riv);
  assets_manager_add(am, data_rudolph_riv);
  assets_manager_add(am, data_flag_riv);
  assets_manager_add(am, data_iron_giant2_riv);
  assets_manager_add(am, data_marker_riv);
  assets_manager_add(am, data_cute_cake_riv);
  assets_manager_add(am, data_diamond_riv);
  assets_manager_add(am, data_zombie_riv);
  assets_manager_add(am, data_working_as_a_team_riv);
  assets_manager_add(am, data_weather_icon_example_riv);
  assets_manager_add(am, data_mail_riv);
  assets_manager_add(am, data_space_camp_riv);
  assets_manager_add(am, data_bear_riv);
  assets_manager_add(am, data_stroke_reflection_effect_riv);
  assets_manager_add(am, data_tv_color_riv);
  assets_manager_add(am, data_question_icon_riv);
  assets_manager_add(am, data_beach_icon_riv);
  assets_manager_add(am, data_dory_riv);
  assets_manager_add(am, data_phone_drop_riv);
  assets_manager_add(am, data_juice063_riv);
  assets_manager_add(am, data_buggy_riv);
  assets_manager_add(am, data_neon_car_riv);
  assets_manager_add(am, data_search_riv);
  assets_manager_add(am, data_truck063_riv);
  assets_manager_add(am, data_notification_icon_3_riv);
  assets_manager_add(am, data_runtime_color_change_riv);
  assets_manager_add(am, data_poison_loader_riv);
  assets_manager_add(am, data_marty_v6_riv);
  assets_manager_add(am, data_flame_and_spark_riv);
  assets_manager_add(am, data_documents3_riv);
  assets_manager_add(am, data_teeny_tiny_file_riv);
  assets_manager_add(am, data_walkcycle_try_riv);
  assets_manager_add(am, data_calendar_icon2_riv);
  assets_manager_add(am, data_knight063_riv);
  assets_manager_add(am, data_barrier_riv);
  assets_manager_add(am, data_hig_five_icon_riv);
  assets_manager_add(am, data_space_reload_riv);
  assets_manager_add(am, data_planet_riv);
  assets_manager_add(am, data_laces_riv);
  assets_manager_add(am, data_marine_corps_running_riv);
  assets_manager_add(am, data_portable_table_riv);
  assets_manager_add(am, image_radio_unchecked_d);
  assets_manager_add(am, image_arrow_up_n);
  assets_manager_add(am, image_arrow_right_p);
  assets_manager_add(am, image_arrow_right_f);
  assets_manager_add(am, image_arrow_up_o);
  assets_manager_add(am, image_arrow_left_o);
  assets_manager_add(am, image_arrow_right_d);
  assets_manager_add(am, image_arrow_left_n);
  assets_manager_add(am, image_check_checked_d);
  assets_manager_add(am, image_radio_checked);
  assets_manager_add(am, image_check_unchecked_d);
  assets_manager_add(am, image_radio_checked_d);
  assets_manager_add(am, image_arrow_down_n);
  assets_manager_add(am, image_arrow_down_o);
  assets_manager_add(am, image_arrow_down_d);
  assets_manager_add(am, image_arrow_down_p);
  assets_manager_add(am, image_arrow_down_f);
  assets_manager_add(am, image_radio_unchecked);
  assets_manager_add(am, image_check_unchecked);
  assets_manager_add(am, image_arrow_up_p);
  assets_manager_add(am, image_arrow_right_n);
  assets_manager_add(am, image_arrow_right_o);
  assets_manager_add(am, image_arrow_up_f);
  assets_manager_add(am, image_arrow_left_d);
  assets_manager_add(am, image_arrow_left_f);
  assets_manager_add(am, image_arrow_up_d);
  assets_manager_add(am, image_arrow_left_p);
  assets_manager_add(am, image_check_checked);
#ifdef WITH_VGCANVAS
#endif /*WITH_VGCANVAS*/
#ifdef WITH_TRUETYPE_FONT
  assets_manager_add(am, font_default);
#else /*WITH_TRUETYPE_FONT*/
#endif /*WITH_TRUETYPE_FONT*/
#endif

  tk_init_assets();
  return RET_OK;
}