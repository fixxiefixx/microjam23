#ifndef MJ_PRACTICE_SCENE_H
#define MJ_PRACTICE_SCENE_H

#include "bn_regular_bg_ptr.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"

#include "mj_scene.h"

namespace mj
{
    class core;

    class practice_scene final : public scene
    {

        public:
            explicit practice_scene(core& core);
        
            ~practice_scene() final;

            [[nodiscard]] bn::optional<scene_type> update() final;

        private:
            core* _core;
            int _selected_game_index = 0;
            int _menu_index=0;
            int _total_game_entries=0;
            bn::regular_bg_ptr _bg;
            bn::vector<bn::sprite_ptr, 8> _game_lines_sprites[12];
            bn::sprite_ptr _cursor_sprite;

            void update_menu();
            void update_cursor();
    };
}

#endif