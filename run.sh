valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --suppressions=mlx.supp \
  ./cub3d maps/cheese_maze.cub
