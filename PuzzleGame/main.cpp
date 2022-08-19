#include <SFML/Graphics.hpp>

using namespace sf;

int main(void)
{
	RenderWindow app(VideoMode(256, 256), "PuzzleGame"); // 그림사이즈는 2의 배수로 하는것이 좋다!
	app.setFramerateLimit(60); //1초동안 60개의애니메이션을 실행? 적용? 할 수 있음

	Texture t;
	t.loadFromFile("images/15.png");

	int grid[6][6] = { 0, }; //


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