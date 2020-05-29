//
// Created by Ignacio Rossi on 4/7/18.
//

#include "gfx/sprite_sheet.hpp"
#include "prelude.hpp"
#include "sdl/mock_texture.hpp"

using ::gfx::SpriteSheetImpl;
using ::sdl::CopySource;
using ::sdl::Texture;
using ::testing::Return;
using ::testing::StrictMock;

void assertCopySource(const CopySource &source, Texture *texture, int x, int y, int w, int h) {
  REQUIRE(&source.texture() == texture);
  REQUIRE(source.width() == w);
  REQUIRE(source.height() == h);
  auto rect = source.rect();
  REQUIRE(rect != nullptr);
  REQUIRE(rect->x == x);
  REQUIRE(rect->y == y);
  REQUIRE(rect->w == w);
  REQUIRE(rect->h == h);
};

SCENARIO("SpriteSheets which fit nicely in the Texture", "[gfx][sprite_sheet]") {
  StrictMock<MockTexture> texture;
  GIVEN("A SpriteSheet constructed from a Texture which fits nicely") {
    EXPECT_CALL(texture, width()).WillRepeatedly(Return(60));
    EXPECT_CALL(texture, height()).WillRepeatedly(Return(60));
    SpriteSheetImpl spriteSheet{texture, 20, 30};
    THEN("It has the correct dimensions") {
      REQUIRE(spriteSheet.size() == 6);
      REQUIRE(spriteSheet.width() == 3);
      REQUIRE(spriteSheet.height() == 2);
    }
    AND_THEN("It clips sprites correctly by index") {
      assertCopySource(spriteSheet.get(0), &texture, 0, 0, 20, 30);
      assertCopySource(spriteSheet.get(1), &texture, 20, 0, 20, 30);
      assertCopySource(spriteSheet.get(2), &texture, 40, 0, 20, 30);
      assertCopySource(spriteSheet.get(3), &texture, 0, 30, 20, 30);
      assertCopySource(spriteSheet.get(4), &texture, 20, 30, 20, 30);
      assertCopySource(spriteSheet.get(5), &texture, 40, 30, 20, 30);
    }
    AND_THEN("It throws on invalid indexes") {
      CHECK_THROWS(spriteSheet.get(-1));
      CHECK_THROWS(spriteSheet.get(6));
      CHECK_THROWS(spriteSheet.get(10));
    }
    AND_THEN("It clips sprites correctly by coordinates") {
      assertCopySource(spriteSheet.get(0, 0), &texture, 0, 0, 20, 30);
      assertCopySource(spriteSheet.get(1, 0), &texture, 20, 0, 20, 30);
      assertCopySource(spriteSheet.get(2, 0), &texture, 40, 0, 20, 30);
      assertCopySource(spriteSheet.get(0, 1), &texture, 0, 30, 20, 30);
      assertCopySource(spriteSheet.get(1, 1), &texture, 20, 30, 20, 30);
      assertCopySource(spriteSheet.get(2, 1), &texture, 40, 30, 20, 30);
    }
    AND_THEN("It throws on invalid coordinates") {
      CHECK_THROWS(spriteSheet.get(-1, 0));
      CHECK_THROWS(spriteSheet.get(3, 0));
      CHECK_THROWS(spriteSheet.get(0, -1));
      CHECK_THROWS(spriteSheet.get(0, 2));
      CHECK_THROWS(spriteSheet.get(-1, -1));
      CHECK_THROWS(spriteSheet.get(-1, 2));
      CHECK_THROWS(spriteSheet.get(3, -1));
      CHECK_THROWS(spriteSheet.get(3, 2));
    }
  }
}

SCENARIO("SpriteSheets which do not fit nicely in the Texture", "[gfx][sprite_sheet]") {
  StrictMock<MockTexture> texture;
  GIVEN("A SpriteSheet constructed from a Texture which does not fit nicely") {
    EXPECT_CALL(texture, width()).WillRepeatedly(Return(60));
    EXPECT_CALL(texture, height()).WillRepeatedly(Return(60));
    SpriteSheetImpl spriteSheet{texture, 29, 14};
    THEN("It has the correct dimensions") {
      REQUIRE(spriteSheet.size() == 8);
      REQUIRE(spriteSheet.width() == 2);
      REQUIRE(spriteSheet.height() == 4);
    }
    AND_THEN("It clips sprites correctly by index") {
      assertCopySource(spriteSheet.get(0), &texture, 0, 0, 29, 14);
      assertCopySource(spriteSheet.get(1), &texture, 29, 0, 29, 14);
      assertCopySource(spriteSheet.get(2), &texture, 0, 14, 29, 14);
      assertCopySource(spriteSheet.get(3), &texture, 29, 14, 29, 14);
      assertCopySource(spriteSheet.get(4), &texture, 0, 28, 29, 14);
      assertCopySource(spriteSheet.get(5), &texture, 29, 28, 29, 14);
      assertCopySource(spriteSheet.get(6), &texture, 0, 42, 29, 14);
      assertCopySource(spriteSheet.get(7), &texture, 29, 42, 29, 14);
    }
    AND_THEN("It throws on invalid indexes") {
      CHECK_THROWS(spriteSheet.get(-1));
      CHECK_THROWS(spriteSheet.get(8));
      CHECK_THROWS(spriteSheet.get(23));
    }
    AND_THEN("It clips sprites correctly by coordinates") {
      assertCopySource(spriteSheet.get(0, 0), &texture, 0, 0, 29, 14);
      assertCopySource(spriteSheet.get(1, 0), &texture, 29, 0, 29, 14);
      assertCopySource(spriteSheet.get(0, 1), &texture, 0, 14, 29, 14);
      assertCopySource(spriteSheet.get(1, 1), &texture, 29, 14, 29, 14);
      assertCopySource(spriteSheet.get(0, 2), &texture, 0, 28, 29, 14);
      assertCopySource(spriteSheet.get(1, 2), &texture, 29, 28, 29, 14);
      assertCopySource(spriteSheet.get(0, 3), &texture, 0, 42, 29, 14);
      assertCopySource(spriteSheet.get(1, 3), &texture, 29, 42, 29, 14);
    }
    AND_THEN("It throws on invalid coordinates") {
      CHECK_THROWS(spriteSheet.get(-1, 0));
      CHECK_THROWS(spriteSheet.get(2, 0));
      CHECK_THROWS(spriteSheet.get(0, -1));
      CHECK_THROWS(spriteSheet.get(0, 4));
      CHECK_THROWS(spriteSheet.get(-1, -1));
      CHECK_THROWS(spriteSheet.get(-1, 4));
      CHECK_THROWS(spriteSheet.get(2, -1));
      CHECK_THROWS(spriteSheet.get(2, 4));
    }
  }
}
