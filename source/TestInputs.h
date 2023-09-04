
#include <string>
#include <vector>

// Test cases (section Examples of patterns):
// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

// Still lifes
//- 1 => Block
//- 2 => Bee-hive
//- 3 => Loaf
//- 4 => Boat
//- 5 => Tub

// Oscillators
//- 6 => Blinker
//- 7 => Toad
//- 8 => Beacon
//- 9 => Pulsar
//- 10 => Penta-decathlon

// Spaceships
//- 11 => Glider
//- 12 => Light-weight spaceship
//- 13 => Middle-weight spaceship
//- 14 => Heavy-weight spaceship

std::vector<std::string> GetTestInputs(int id)
{
	std::vector<std::string> inputs;

	if (id == 1) // Block
	{
		inputs.push_back("4x4");

		inputs.push_back("1x1"); inputs.push_back("1x2");
		inputs.push_back("2x1"); inputs.push_back("2x2");
	}
	else if (id == 2) // Bee-hive
	{
		inputs.push_back("6x5");

		inputs.push_back("1x2");
		inputs.push_back("2x1"); inputs.push_back("2x3");
		inputs.push_back("3x1"); inputs.push_back("3x3");
		inputs.push_back("4x2");
	}
	else if (id == 3) // Loaf
	{
		inputs.push_back("6x6");

		inputs.push_back("1x2");
		inputs.push_back("2x1"); inputs.push_back("2x3");
		inputs.push_back("3x1"); inputs.push_back("3x4");
		inputs.push_back("4x2"); inputs.push_back("4x3");
	}
	else if (id == 4) // Boat
	{
		inputs.push_back("5x5");

		inputs.push_back("1x1"); inputs.push_back("1x2");
		inputs.push_back("2x1"); inputs.push_back("2x3");
		inputs.push_back("3x2");
	}
	else if (id == 5) // Tub
	{
		inputs.push_back("5x5");

		inputs.push_back("1x2");
		inputs.push_back("2x1"); inputs.push_back("2x3");
		inputs.push_back("3x2");
	}
	else if (id == 6) // Blinker
	{
		inputs.push_back("5x5");

		inputs.push_back("2x1"); inputs.push_back("2x2"); inputs.push_back("2x3");
	}
	else if (id == 7) // Toad
	{
		inputs.push_back("6x6");

		inputs.push_back("1x3");
		inputs.push_back("2x2"); inputs.push_back("2x3");
		inputs.push_back("3x2"); inputs.push_back("3x3");
		inputs.push_back("4x2");
	}
	else if (id == 8) // Beacon
	{
		inputs.push_back("6x6");

		inputs.push_back("1x1"); inputs.push_back("1x2");
		inputs.push_back("2x1"); inputs.push_back("2x2");
		inputs.push_back("3x3"); inputs.push_back("3x4");
		inputs.push_back("4x3"); inputs.push_back("4x4");
	}
	else if (id == 9) // Pulsar
	{
		inputs.push_back("17x17");

		inputs.push_back("1x5"); inputs.push_back("1x11");

		inputs.push_back("2x5"); inputs.push_back("2x11");

		inputs.push_back("3x5"); inputs.push_back("3x6");
		inputs.push_back("3x10"); inputs.push_back("3x11");

		inputs.push_back("5x1"); inputs.push_back("5x2"); inputs.push_back("5x3");
		inputs.push_back("5x6"); inputs.push_back("5x7"); inputs.push_back("5x9");
		inputs.push_back("5x10"); inputs.push_back("5x13"); inputs.push_back("5x14");
		inputs.push_back("5x15");

		inputs.push_back("6x3"); inputs.push_back("6x5"); inputs.push_back("6x7");
		inputs.push_back("6x9"); inputs.push_back("6x11"); inputs.push_back("6x13");

		inputs.push_back("7x5"); inputs.push_back("7x6"); inputs.push_back("7x10");
		inputs.push_back("7x11");

		inputs.push_back("9x5"); inputs.push_back("9x6");
		inputs.push_back("9x10"); inputs.push_back("9x11");

		inputs.push_back("10x3"); inputs.push_back("10x5"); inputs.push_back("10x7");
		inputs.push_back("10x9"); inputs.push_back("10x11"); inputs.push_back("10x13");

		inputs.push_back("11x1"); inputs.push_back("11x2"); inputs.push_back("11x3");
		inputs.push_back("11x6"); inputs.push_back("11x7"); inputs.push_back("11x9");
		inputs.push_back("11x10"); inputs.push_back("11x13"); inputs.push_back("11x14");
		inputs.push_back("11x15");

		inputs.push_back("13x5"); inputs.push_back("13x6");
		inputs.push_back("13x10"); inputs.push_back("13x11");

		inputs.push_back("14x5"); inputs.push_back("14x11");

		inputs.push_back("15x5"); inputs.push_back("15x11");
	}
	else if (id == 10) // Penta-decathlon
	{
		inputs.push_back("11x18");

		inputs.push_back("4x3"); inputs.push_back("4x6"); inputs.push_back("4x8");
		inputs.push_back("4x9"); inputs.push_back("4x11"); inputs.push_back("4x14");

		inputs.push_back("5x3"); inputs.push_back("5x4"); inputs.push_back("5x5");
		inputs.push_back("5x6"); inputs.push_back("5x8"); inputs.push_back("5x9");
		inputs.push_back("5x11"); inputs.push_back("5x12"); inputs.push_back("5x13");
		inputs.push_back("5x14");

		inputs.push_back("6x3"); inputs.push_back("6x6"); inputs.push_back("6x8");
		inputs.push_back("6x9"); inputs.push_back("6x11"); inputs.push_back("6x14");
	}
	else if (id == 11) // Glider
	{
		inputs.push_back("20x20");

		inputs.push_back("1x3");
		inputs.push_back("2x1"); inputs.push_back("2x3");
		inputs.push_back("3x2"); inputs.push_back("3x3");
	}
	else if (id == 12) // Light-weightspaceship
	{
		inputs.push_back("30x8");

		inputs.push_back("1x1"); inputs.push_back("1x3");
		inputs.push_back("2x4");
		inputs.push_back("3x4");
		inputs.push_back("4x1"); inputs.push_back("4x4");
		inputs.push_back("5x2"); inputs.push_back("5x3"); inputs.push_back("5x4");
	}
	else if (id == 13) // Middle-weightspaceship
	{
		inputs.push_back("30x8");

		inputs.push_back("1x4"); inputs.push_back("1x6");
		inputs.push_back("2x3");
		inputs.push_back("3x3"); inputs.push_back("3x7");
		inputs.push_back("4x3");
		inputs.push_back("5x3"); inputs.push_back("5x6");
		inputs.push_back("6x3"); inputs.push_back("6x4"); inputs.push_back("6x5");
	}
	else if (id == 14) // Heavy-weightspaceship
	{
		inputs.push_back("30x8");

		inputs.push_back("1x4"); inputs.push_back("1x6");
		inputs.push_back("2x3");
		inputs.push_back("3x3"); inputs.push_back("3x7");
		inputs.push_back("4x3"); inputs.push_back("4x7");
		inputs.push_back("5x3");
		inputs.push_back("6x3"); inputs.push_back("6x6");
		inputs.push_back("7x3"); inputs.push_back("7x4"); inputs.push_back("7x5");
	}

	if (inputs.size() != 0)
		inputs.push_back("s");

	return inputs;
}
