/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:58:52 by jdidier           #+#    #+#             */
/*   Updated: 2021/03/05 20:12:57 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "stdio.h"

# define TILE_SIZE 32
# define FOV 66
# define RESOLUTION "R"
# define NORTH_TEXTURE "NO"
# define SOUTH_TEXTURE "SO"
# define WEST_TEXTURE "WE"
# define EAST_TEXTURE "EA"
# define SPRITE_TEXTURE "S"
# define FLOOR_COLOR "F"
# define CEILING_COLOR "C"

typedef	struct		s_player
{
	int				turn;
	int				walk;
	int				straf;
	double			x;
	double			y;
	double			angle;
	double			spd;
	double			rotspd;
}					t_player;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef	struct		s_data
{
	int				img_size;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	char			*img_data;
	void			*img_ptr;
}					t_data;

typedef	struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef	struct		s_sprite
{
	int				visible;
	unsigned int	unvi_col;
	double			x;
	double			y;
	double			wx;
	double			w;
	double			h;
	double			distance;
	double			angle;
}					t_sprite;

typedef	struct		s_ray
{
	int				hor;
	double			dst;
	t_point			inter;
}					t_ray;

typedef struct		s_map
{
	int				player_parsed;
	int				inmap;
	int				blank;
	int				w;
	int				h;
	char			**g;
}					t_map;

typedef struct		s_cub3d
{
	int				w_width;
	int				w_height;
	int				f_color;
	int				c_color;
	int				n_sprites;
	int				save;
	double			dstprojplane;
	double			*raydst;
	void			*mlx;
	void			*win;
	int				*stripeh;
	t_list			*imgs;
	t_data			img;
	t_player		player;
	t_data			tab[5];
	t_map			map;
	t_sprite		*spts;
	t_sprite		*vis;
}					t_cub3d;

typedef	struct		s_token
{
	int				len;
	int				num;
	int				parsed;
	char			*elem;
	void			(*func)(t_cub3d *cub, char **str);
}					t_token;

typedef	struct		s_error
{
	int				id;
	char			*msg;
}					t_error;

t_player			init_player(double x, double y, double angle);
void				init_cub(t_cub3d *cub);
void				init_event(t_cub3d *cub);
void				init_parse(t_cub3d *cub, char *file);
void				init(t_cub3d *cub);
void				setup(t_cub3d *cub);
int					gameloop(t_cub3d *cub);
char				*format_line_to_map(t_cub3d *cub, char *s);
int					ft_exit(t_cub3d *cub);
void				send_error(int id, t_cub3d *cub);
int					iswall(char **map, double x, double y);
int					issprite(char **map, double x, double y);
void				update_mov(t_cub3d *cub);
void				update_walk(t_cub3d *cub);
void				update_straf(t_cub3d *cub);
int					key_press(int key, t_cub3d *cub);
int					key_release(int key, t_cub3d *cub);
double				normalize_angle(double angle);
float				deg2rad(float angle);
double				dst2pnts(double x1, double y1, double x2, double y2);
int					isfaceup(double angle);
int					isfacedown(double angle);
int					isfaceleft(double angle);
int					isfaceright(double angle);
t_point				horizontal_inter(t_cub3d *cub, double angle);
t_point				vertical_inter(t_cub3d *cub, double angle);
t_ray				raycast(t_cub3d *cub, double angle);
t_ray				new_ray(t_point inter, double dst, int type);
void				render_wall(t_cub3d *cub, char *img_data);
void				draw_background(t_cub3d *cub);
int					check_ext(char *path, char *ext);
void				parse(int fd, t_cub3d *cub);
int					create_trgb(int t, int r, int g, int b);
void				parse(int fd, t_cub3d *cub);
void				parse_line(char *line, t_cub3d *cub);
void				parse_map(char *line, t_cub3d *cub);
void				get_player_pos(t_cub3d *cub, char *s);
void				parse_player_pos(t_cub3d *cub, int x, int direction);
void				parse_res(t_cub3d *cub, char **str);
void				parse_path(t_cub3d *cub, char **str);
void				parse_rgb(t_cub3d *cub, char **str);
int					is_directory(int fd);
int					strisrgb(char *str);
void				del_split(char **tab);
int					splitlen(char **str);
int					isallparsed();
int					isstrdig(char *str);
int					ismap(char *str);
void				check_map(t_cub3d *cub);
t_data				new_texture(t_cub3d *cub, char *path);
unsigned int		get_pixel_color(t_data *texture, int x, int y);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_wall(int x, t_cub3d *cub, t_ray ray, t_data *text);
t_data				*get_wall_text(t_cub3d *cub, double angle, int type);
void				save(t_cub3d *cub, t_data *img);
void				header(t_cub3d *cub, t_data *img, int fd);
t_sprite			*init_sprites(t_cub3d *cub);
int					get_nb_sprites(t_cub3d *cub);
t_sprite			new_sprite(int x, int y);
t_sprite			*fill_visible(int nb, t_cub3d *cub);
int					get_nb_visible_sprites(t_cub3d *cub);
void				draw_sprite(t_data *text, t_sprite *spt, int x,
					t_cub3d *cub);
void				render_sprites(t_cub3d *cub);
void				sortvisibles(t_sprite *visibles, int nb);

#endif
