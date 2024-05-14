#include "UserOptions.hpp"

#include <math.h>

UserOptions::UserOptions(const unsigned int& field_of_view, const unsigned int& screen_width, const unsigned int& screen_height, const unsigned int& view_distance, const int& pixels_per_ray) {
	ui_fov = field_of_view;
	ui_height = screen_height;
	ui_width = screen_width;
	ui_render_dist = view_distance;
	ui_pix_ray = pixels_per_ray;


	max_ray_iterations = view_distance * 10;


	pixel_width = floor((double)screen_width / 2);
	pixel_height = screen_height;
	
	pixel_off = (pixel_width*2 != ui_width);
	pixel_multiplier = abs(pixels_per_ray);

	horizontal_fov = field_of_view;
	vertical_fov = round(field_of_view * screen_height / screen_width);
}

void UserOptions::ChangeOptions(const unsigned int& field_of_view, const unsigned int& screen_width, const unsigned int& screen_height, const unsigned int& view_distance, const int& pixels_per_ray) {
	ui_fov = field_of_view;
	ui_height = screen_height;
	ui_width = screen_width;
	ui_render_dist = view_distance;
	ui_pix_ray = pixels_per_ray;


	max_ray_iterations = view_distance * 10;


	pixel_width = floor((double)screen_width / 2);
	pixel_height = screen_height;

	pixel_off = (pixel_width * 2 != ui_width);
	pixel_multiplier = abs(pixels_per_ray);

	horizontal_fov = field_of_view;
	vertical_fov = round(field_of_view * screen_height / screen_width);
}
