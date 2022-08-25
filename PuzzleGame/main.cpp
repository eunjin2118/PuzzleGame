#include <SFML/Graphics.hpp>

using namespace sf;

int main(void)
{
	RenderWindow app(VideoMode(256, 256), "PuzzleGame"); // 그림사이즈는 2의 배수로 하는것이 좋다!
	app.setFramerateLimit(60); //1초동안 60개의애니메이션을 실행? 적용? 할 수 있음

	Texture t;
	t.loadFromFile("images/15.png");

	int grid[6][6] = { 0, }; // 1~15 : 해당 숫자, 16 : 빈공간, 0 : 벽


	int w = 64; // 퍼즐 하나의 폭

	// 스프라이트개수를 최적화
	Sprite sprite[17];

	int number = 1;
	// 그림을 쪼개고 논리적으로 매칭(좌표와 행렬, 그림과 숫자)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) 
		{
			sprite[number].setTexture(t); //Texture선정
			// 시작점의 좌표를 구하고 폭, 높이 구해서 가져오기
			// ex) 2번 : 64, 0 / 6번: 64, 64
			// 행 -> Y축, 열 -> X축
			sprite[number].setTextureRect(IntRect(j*w, i*w, w, w)); // 특정한 좌표에 있는 그림 가져오기
			grid[i + 1][j + 1] = number; // 그림이 무엇인지 나타냄, 1부터 시작으로 설정
			number++;
		}
	}

	while (app.isOpen())
	{
		Event e; 
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				app.close();
			}

			// 마우스에 대한 interface추가
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					// 마우스의 좌표 가져오기
					Vector2i pos = Mouse::getPosition(app);
					int x = pos.x / w + 1; // 1행, 1열로 맞췄으니까 1 더해주기
					int y = pos.y / w + 1;

					// swap
					// 밑으로 움직이기
					int dx = 0, dy = 0;
					if (grid[y + 1][x] == 16) {dx = 0; dy = 1;}
					// 위로 움직이기
					if (grid[y - 1][x] == 16) { dx = 0; dy = -1; }
					// 오른쪽으로 움직이기
					if (grid[y][x+1] == 16) { dx = 1; dy = 0; }
					// 왼쪽으로 움직이기
					if (grid[y][x - 1] == 16) { dx = -1; dy = 0; }
					int temp = grid[y][x];
					grid[y][x] = 16;
					grid[y + dy][x + dx] = temp;

					// 모션(애니메이션)
					sprite[16].move(-dx * (float)w, -dy * (float)w);
					float speed = 3.f;

					for (int i = 0; i < w; i += (int)speed) 
					{
						sprite[temp].move(dx * speed, dy * speed);
						app.draw(sprite[16]);
						app.draw(sprite[temp]);
						app.display();
					}
				}
			}
		}

		app.clear(Color::White);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int n = grid[i+1][j+1];
				sprite[n].setPosition(j * w, i * w);
				app.draw(sprite[n]);
			}
		}
		app.display();
	}

	return 0;
}