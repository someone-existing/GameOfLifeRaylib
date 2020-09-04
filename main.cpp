#include <raylib.h>
#include <iostream>

#define screenWidth 1366
#define screenHeight 768
#define res 10

void Draw(int grid[screenWidth/res][screenHeight/res])
{
	for(int i = 0; i < screenWidth/res; i++) {
		for(int j = 0; j < screenHeight/res; j++) {
			if(grid[i][j] == 1) {
				DrawRectangle(res*i, res*j,res-1, res-1, {20, 20, 20, 255});
			} else {
				DrawRectangle(res*i, res*j,res-1, res-1, WHITE);
			}
		}
	}
}
int main(int argc, char* argv[])
{
	InitWindow(screenWidth, screenHeight, "Game of life");
	ToggleFullscreen();
	SetTargetFPS(20);

	int grid[screenWidth/res][screenHeight/res];
	int newgrid[screenWidth/res][screenHeight/res];
	for(int i = 0; i < screenWidth/res; i++) {
		for(int j = 0; j < screenHeight/res; j++) {
			grid[i][j] = GetRandomValue(0, 1);
		}
	}
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		for(int i = 0; i < screenWidth/res; i++) {
			for(int j = 0; j < screenHeight/res; j++) {
				int neighbours_sum = 0;
				neighbours_sum = (grid[i-1][j-1]+grid[i][j-1]+grid[i+1][j-1])+
				                 (grid[i-1][j]+grid[i+1][j])+
				                 (grid[i-1][j+1]+grid[i][j+1]+grid[i+1][j+1]);
				if(grid[i][j] == 0 && neighbours_sum==3) {
					newgrid[i][j] = 1;
				} else if(grid[i][j] == 1) {
					if(neighbours_sum < 2 || neighbours_sum > 3) {
						newgrid[i][j] = 0;
					}
				}
			}
		}


		for(int i = 0; i < screenWidth/res; i++) {
			for(int j = 0; j < screenHeight/res; j++) {
				grid[i][j] = newgrid[i][j];
			}
		}
		Draw(grid);

		EndDrawing();

	}

	CloseWindow();
	return 0;
}
