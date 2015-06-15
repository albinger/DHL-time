#include <pebble.h>

Window *my_window;
TextLayer *text_layer, *zulu_layer;
BitmapLayer *bitmap_layer;
GBitmap *BackgroundImage;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  struct tm *gmt_time = gmtime(&temp);
  static char time[] = "00:00";
  static char ztime[] = "00:00";
  strftime(time, sizeof(time), "%H:%M", tick_time);
  text_layer_set_text(text_layer, time);
  strftime(ztime,sizeof(time), "%H:%M",gmt_time);
  text_layer_set_text(zulu_layer,ztime);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

void handle_init(void) {
  my_window = window_create();
  BackgroundImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DHL);
   //Create GBitmap, then set to created BitmapLayer
  bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(bitmap_layer, BackgroundImage);
  bitmap_layer_set_compositing_mode(bitmap_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(bitmap_layer));
  
  text_layer = text_layer_create(GRect(0, 8, 144, 48));
  text_layer_set_font(text_layer,fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_LCD_48)));
  text_layer_set_text_color(text_layer,GColorBlack);
  text_layer_set_background_color(text_layer,GColorClear);
  text_layer_set_text_alignment(text_layer,GTextAlignmentCenter);
  text_layer_set_text(text_layer,"88:88");
  layer_add_child(window_get_root_layer(my_window),text_layer_get_layer(text_layer));
  
  zulu_layer = text_layer_create(GRect(0, 100, 144, 48));
  text_layer_set_font(zulu_layer,fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_LCD_48)));
  text_layer_set_text_color(zulu_layer,GColorBlack);
  text_layer_set_background_color(zulu_layer,GColorClear);
  text_layer_set_text_alignment(zulu_layer,GTextAlignmentCenter);
  text_layer_set_text(zulu_layer,"88:88");
  layer_add_child(window_get_root_layer(my_window),text_layer_get_layer(zulu_layer));
  
  window_stack_push(my_window, true);
   tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
}

void handle_deinit(void) {
  tick_timer_service_unsubscribe();
  text_layer_destroy(text_layer);
  text_layer_destroy(zulu_layer);
  bitmap_layer_destroy(bitmap_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
