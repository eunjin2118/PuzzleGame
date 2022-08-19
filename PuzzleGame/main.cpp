#include <SFML/Graphics.hpp>

using namespace sf;

int main(void)
{
	RenderWindow app(VideoMode(256, 256), "PuzzleGame"); // 그림사이즈는 2의 배수로 하는것이 좋다!
	app.setFramerateLimit(60); //1초동안 60개의애니메이션을 실행? 적용? 할 수 있음

	Texture t;
	t.loadFromFile("imegas/15.png");

	int w = 64; // 퍼즐 하나의 폭
	return 0;
}