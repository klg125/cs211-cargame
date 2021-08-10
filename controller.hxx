#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
public:
    explicit Controller(Model&);

protected:

    void on_frame(double dt) override;

    ge211::Dims<int> initial_window_dimensions() const override;

    void draw(ge211::Sprite_set& set) override;

    Model& model_;
    View view_;
    void
    on_key(ge211::Key key);
};
