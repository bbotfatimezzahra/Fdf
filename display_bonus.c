#include "fdf.h"

int	key_hook(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
		terminate(" ", fdf);
	if (keysym == XK_i || keysym == XK_I
			|| keysym == XK_o || keysym == XK_O )
		zoom(fdf, keysym);
	if (keysym == XK_Down || keysym == XK_Up
		|| keysym == XK_Left || keysym == XK_Right)
		move(fdf, keysym);
	if (keysym == XK_z || keysym == XK_Z || keysym == XK_a
		|| keysym == XK_A || keysym == XK_x || keysym == XK_X)
		rotate(fdf, keysym);
	if (keysym == XK_s || keysym == XK_S || keysym == XK_y
		|| keysym == XK_Y || keysym == XK_h || keysym == XK_H)
		rotate(fdf, keysym);
	if (keysym == XK_b || keysym == XK_B)
		reset(fdf, keysym);
	return (0);
}

int	destroy(t_fdf *fdf)
{
	terminate(" ", fdf);
	return (0);
}

void	start_display(t_fdf *fdf)
{
	int		*l_length;
	int		*endian;
	char	*title;

	l_length = &fdf->line_length;
	endian = &fdf->endian;
	title = "FDF PROJECT ***FBBOT***";
	fdf->con = mlx_init();
	if (!fdf->con)
		terminate(ERR_CON, fdf);
	fdf->win = mlx_new_window(fdf->con, fdf->width, fdf->length, title);
	if (!fdf->win)
		terminate(ERR_WIN, fdf);
	fdf->img = mlx_new_image(fdf->con, fdf->width, fdf->length);
	if (!fdf->img)
		terminate(ERR_IMG, fdf);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, l_length, endian);
	fill_image(fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->win, 17, 1L << 2, destroy, fdf);
	mlx_loop(fdf->con);
}
