#pragma once
class UserOptions {
public:
	UserOptions(const unsigned int & field_of_view = 70, const unsigned int & screen_height = 30, const unsigned int & screen_width = 50, const unsigned int& view_distance  = 10, const int& pixels_per_ray = 1);
	void ChangeOptions(const unsigned int& field_of_view = 70, const unsigned int& screen_height = 30, const unsigned int& screen_width = 50, const unsigned int& view_distance = 10, const int& pixels_per_rsay = 1);
	
	unsigned int ui_fov;
	int ui_pix_ray;
	unsigned int ui_height;
	unsigned int ui_width;
	unsigned int ui_render_dist;

	unsigned int pixel_height;
	unsigned int pixel_width;
	bool pixel_off;
	int pixel_multiplier;
	unsigned int horizontal_fov;
	unsigned int vertical_fov;
	unsigned int max_ray_iterations;

private:
};