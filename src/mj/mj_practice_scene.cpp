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
#include "bn_sprite_items_mj_small_pumpkin.h"

namespace mj
{
    practice_scene::practice_scene(core& core):
    _bg(bn::regular_bg_items::mj_op_e_bg.create_bg(0,0)),
    _cursor_sprite(bn::sprite_items::mj_small_pumpkin.create_sprite(-25, 0, 12))
    {
        _core = &core;

        bn::span<const bn::string_view> game_names = game_list::get_game_names();
        _total_game_entries = game_names.size();

        if(core.practice_game_index!=-1)
        {
            _selected_game_index = core.practice_game_index;
        }

        update_menu();
        update_cursor();
    }

    practice_scene::~practice_scene()
    {     
        bn::bg_palettes::set_fade_intensity(0);
        bn::sprite_palettes::set_fade_intensity(0);
    }

    void practice_scene::update_menu()
    {
        bn::sprite_text_generator& text_generator = _core->small_text_generator();
        int game_line_count = sizeof(_game_lines_sprites) / sizeof(_game_lines_sprites[0]);

        bn::span<const bn::string_view> game_names = game_list::get_game_names();

        for(int i = 0;i<game_line_count;i++)
        {
            _game_lines_sprites[i].clear();
        }

        for(int i=0; i<game_line_count && i+_menu_index<game_names.size();i++)
        {
            text_generator.set_left_alignment();
            bn::string<32> text;
            bn::ostringstream text_stream(text);
            text_stream.append(i+_menu_index);
            text_stream.append(" ");
            text_stream.append(game_names.at(i+_menu_index));
            
            text_generator.generate(-14,12 - (160 / 2) +(12*i),text,_game_lines_sprites[i]);
        }
    }

    void practice_scene::update_cursor()
    {
        int game_line_count = sizeof(_game_lines_sprites) / sizeof(_game_lines_sprites[0]);

        int row = _selected_game_index - _menu_index;
        if(row<0 || row >= game_line_count)
        {
            int menu_page = _selected_game_index / game_line_count;
            _menu_index = menu_page * game_line_count;
            update_menu();
        }
        row = _selected_game_index - _menu_index;

        _cursor_sprite.set_y(12 - (160 / 2) +(12*row));
    }

    bn::optional<scene_type> practice_scene::update()
    {
        bn::optional<scene_type> result;
        if(bn::keypad::b_pressed())
        {
            _core->practice_game_index=-1;
            result=scene_type::TITLE;
        }
        else if(bn::keypad::a_pressed())
        {
            _core->practice_game_index=_selected_game_index;
            result=scene_type::GAME;
        }
        else if(bn::keypad::down_pressed())
        {
            _selected_game_index++;
            if(_selected_game_index>=_total_game_entries)
            {
                _selected_game_index = 0;
            }
            update_cursor();
        }
        else if(bn::keypad::up_pressed())
        {
            _selected_game_index--;
            if(_selected_game_index < 0)
            {
                _selected_game_index = _total_game_entries-1;
            }
            update_cursor();
        }
        return result;
    }
}