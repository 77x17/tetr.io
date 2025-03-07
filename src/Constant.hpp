#pragma once

static const int WINDOW_WIDTH       = 800;
static const int WINDOW_HEIGHT      = 700;

static const int       NUM_BLOCK    = 4;
static const int       BLOCK_SIZE   = 30;
// static constexpr float DROP_TIME    = 0.5f; 
static constexpr float DROP_TIME    = 0.5f; 

static const int HOLD_POSITION_X    = 50;
static const int HOLD_POSITION_Y    = 50 + 30;
static const int HOLD_WIDTH         = 4;
static const int HOLD_HEIGHT        = 3;

static const int GRID_POSITION_X    = HOLD_POSITION_X + BLOCK_SIZE * (HOLD_WIDTH + 1);
static const int GRID_POSITION_Y    = 50;
static const int GRID_WIDTH         = 10;
static const int GRID_HEIGHT        = 20;

static const int NEXT_POSITION_X    = GRID_POSITION_X + BLOCK_SIZE * (GRID_WIDTH + 1);
static const int NEXT_POSITION_Y    = 50 + 30;
static const int NEXT_WIDTH         = 4;
static const int NEXT_HEIGHT        = 15;

static const int NUM_SHAPE          = 7;
static const int SHAPE_WIDTH        = 4;
static const int SHAPE_HEIGHT       = 2;