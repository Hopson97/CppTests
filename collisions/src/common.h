#pragma once

constexpr int WORLD_SIZE = 16;
constexpr int TILE_SIZE = 32;
constexpr int PLAYER_SIZE = TILE_SIZE - 5;

constexpr int WIN_WIDTH = TILE_SIZE * WORLD_SIZE + 50;
constexpr int WIN_HEIGHT = TILE_SIZE * WORLD_SIZE + 20;

constexpr float ACCELERATION = 0.45f;

constexpr float PI = 3.14159;