#include "mj/mj_practice_scene.h"

#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_palettes.h"
#include "bn_keypad.h"
#include "bn_string.h"

#include "mj/mj_core.h"
#include "mj/mj_scene_type.h"
#include "mj/mj_game_list.h"

#include "bn_regular_bg_items_mj_op_e_bg.h"

namespace mj
{
    practice_scene::practice_scene(core& core):
    _bg(bn::regular_bg_items::mj_op_e_bg.create_bg(0,0))
    {
        bn::sprite_text_generator& text_generator = core.small_text_generator();
        int game_line_count = sizeof(_game_lines_sprites) / sizeof(_game_lines_sprites[0]);

        bn::span<const bn::string_view> game_names = game_list::get_game_names();

        for(int i=0; i<game_line_count && i<game_names.size();i++)
        {
            text_generator.set_left_alignment();
            bn::string<32> text;
            bn::ostringstream text_stream(text);
            text_stream.append(game_names.at(i));
            text_stream.append(i);
            text,_game_lines_sprites[i].clear();
            text_generator.generate(-14,12 - (160 / 2) +(12*i),text,_game_lines_sprites[i]);
        }
    }

    practice_scene::~practice_scene()
    {     
        bn::bg_palettes::set_fade_intensity(0);
        bn::sprite_palettes::set_fade_intensity(0);
    }

    bn::optional<scene_type> practice_scene::update()
    {
        bn::optional<scene_type> result;
        if(bn::keypad::b_pressed())
        {
            result=scene_type::TITLE;
        }
        return result;
    }
}