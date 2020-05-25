//
// Created by Ignacio Rossi on 4/7/18.
//

#include "mock_texture.h"
#include "prelude.h"
#include "sdl/renderer.h"

using sdl::CopyDest;
using sdl::CopySource;
using sdl::TextureImpl;
using ::testing::Return;

SCENARIO("Textures works as CopySources", "[sdl][CopySource]") {
  auto ptr = reinterpret_cast<SDL_Texture *>(0x123456);
  ::testing::StrictMock<MockTexture> texture;
  EXPECT_CALL(texture, width()).WillRepeatedly(Return(10));
  EXPECT_CALL(texture, height()).WillRepeatedly(Return(20));

  //  TextureImpl texture{ptr, 10, 20};
  GIVEN("A CopySource constructed from a Texture") {
    CopySource source{texture};
    THEN("it points to the right texture.") {
      REQUIRE(&source.texture() == &texture);
    }
    AND_THEN("it has the Texture's size.") {
      REQUIRE(source.width() == 10);
      REQUIRE(source.height() == 20);
    }
    AND_THEN("it has a null source rectangle.") {
      REQUIRE(source.rect() == nullptr);
    }
  }

  GIVEN("A CopySource constructed from a Texture with a delimiting rectangle") {
    SDL_Rect rect{1, 2, 3, 4};
    CopySource source{texture, rect};
    THEN("it points to the right texture.") {
      REQUIRE(&source.texture() == &texture);
    }
    AND_THEN("it has the rectangle's size.") {
      REQUIRE(source.width() == 3);
      REQUIRE(source.height() == 4);
    }
    AND_THEN("it has the correct source rectangle.") {
      REQUIRE(*source.rect() == rect);
    }
  }
}

SCENARIO("CopyDests work as expected", "[sdl][CopyDest]") {
  GIVEN("A CopyDest constructed from a point") {
    CopyDest dest{1, 2};
    auto rect = dest.asRect(3, 4);
    THEN("It has the point coordinates") {
      REQUIRE(rect.x == 1);
      REQUIRE(rect.y == 2);
    }
    AND_THEN("It has the given dimensions") {
      REQUIRE(rect.w == 3);
      REQUIRE(rect.h == 4);
    }
  }

  GIVEN("A CopyDest constructed from a rectangle") {
    CopyDest dest{SDL_Rect{1, 2, 3, 4}};
    auto rect = dest.asRect(5, 6);
    THEN("It has the rectangle coordinates") {
      REQUIRE(rect.x == 1);
      REQUIRE(rect.y == 2);
    }
    AND_THEN("It has the rectangle dimensions") {
      REQUIRE(rect.w == 3);
      REQUIRE(rect.h == 4);
    }
  }

  GIVEN("A CopyDest constructed from all four dimensions") {
    CopyDest dest{1, 2, 3, 4};
    auto rect = dest.asRect(5, 6);
    THEN("It has the given coordinates") {
      REQUIRE(rect.x == 1);
      REQUIRE(rect.y == 2);
    }
    AND_THEN("It has the given dimensions") {
      REQUIRE(rect.w == 3);
      REQUIRE(rect.h == 4);
    }
  }
}
