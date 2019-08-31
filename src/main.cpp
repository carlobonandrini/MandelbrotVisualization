#include <SFML/Graphics.hpp>
#include <iostream>

static const sf::Vector3f color_map[] = {
    sf::Vector3f(0.0f, 0.0f, 0.0f),    sf::Vector3f(0.26f, 0.18f, 0.06f),
    sf::Vector3f(0.1f, 0.03f, 0.1f),   sf::Vector3f(0.04f, 0.0f, 0.18f),
    sf::Vector3f(0.02f, 0.02f, 0.29f), sf::Vector3f(0.0f, 0.03f, 0.39f),
    sf::Vector3f(0.05f, 0.17f, 0.54f), sf::Vector3f(0.09f, 0.32f, 0.69f),
    sf::Vector3f(0.22f, 0.49f, 0.82f), sf::Vector3f(0.52f, 0.71f, 0.9f),
    sf::Vector3f(0.82f, 0.92f, 0.97f), sf::Vector3f(0.94f, 0.91f, 0.75f),
    sf::Vector3f(0.97f, 0.79f, 0.37f), sf::Vector3f(1.0f, 0.67f, 0.0f),
    sf::Vector3f(0.8f, 0.5f, 0.0f),    sf::Vector3f(0.6f, 0.34f, 0.0f),
    sf::Vector3f(0.41f, 0.2f, 0.01f)};

static int maxIter = 10;

int MandelbrotIter(double startReal, double startImg);

sf::Color getColor(int count);

int main() {
  const int width = 1500, height = 1500;
  sf::RenderWindow window(sf::VideoMode(width, height),
                          "Mandelbrot Visualization");

  sf::Image image;
  image.create(width, height, sf::Color(0, 0, 0));
  sf::Texture texture;
  sf::Sprite sprite; // Load image

  double zoom = 0.004;
  double offsetX = -0.7;
  double offsetY = 0.0;
  bool changedSomething = true;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        changedSomething = true;
        switch (event.key.code) {
        case sf::Keyboard::Left:
          offsetX -= 40 * zoom;
          break;
        case sf::Keyboard::Right:
          offsetX += 40 * zoom;
          break;
        case sf::Keyboard::Up:
          offsetY -= 40 * zoom;
          break;
        case sf::Keyboard::Down:
          offsetY += 40 * zoom;
          break;
        case sf::Keyboard::Z:
          zoom *= 0.9;
          break;
        case sf::Keyboard::X:
          zoom /= 0.9;
          break;
        case sf::Keyboard::A:
          maxIter += 10;
          break;
        case sf::Keyboard::S:
          if (maxIter > 10)
            maxIter -= 10;
          break;
        default:
          changedSomething = false;
        }
      }
    }

    if (changedSomething) {
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          double real = (x - width / 2.0) * zoom + offsetX;
          double img = (y - height / 2.0) * zoom + offsetY;

          int count = MandelbrotIter(real, img);
          image.setPixel(x, y, getColor(count));
        }
      }
      texture.loadFromImage(image);
      sprite.setTexture(texture);
    }

    window.clear();
    window.draw(sprite);
    window.display();

    changedSomething = false;
  }

  return 0;
}

int MandelbrotIter(double startReal, double startImg) {
  double zReal = startReal;
  double zImag = startImg;

  for (int counter = 0; counter < maxIter; ++counter) {
    double r2 = zReal * zReal;
    double i2 = zImag * zImag;
    if (r2 + i2 > 4.0) {
      return counter;
    }
    zImag = 2.0 * zReal * zImag + startImg;
    zReal = r2 - i2 + startReal;
  }
  return maxIter;
}

sf::Color getColor(int count) {
  int row_index = (count * 100 / maxIter % 17);
  if (count == maxIter)
    return sf::Color(0, 0, 0);
  else {
    return sf::Color(color_map[row_index].x * 255, color_map[row_index].y * 255,
                     color_map[row_index].z * 255);
  }
}
