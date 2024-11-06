#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::Fullscreen();

  // Simple layout with only a leaderboard menu
  auto leaderboard = Renderer([] {
    return vbox({
      text("Leaderboard / Top") | bold,
      separator(),
      text("Bitcoin"),
      text("[Example Graph for Bitcoin]") | color(Color::Green),
    });
  });

  // Sidebar component for navigation
  auto sidebar = Container::Vertical({
    Button("Leaderboard / Top", screen.ExitLoopClosure()),
  });

  auto sidebar_renderer = Renderer(sidebar, [&] {
    return vbox({
      text("Menu") | bold | color(Color::Blue),
      separator(),
      sidebar->Render(),
    }) | border;
  });

  // Layout arrangement
  auto main_container = Container::Horizontal({sidebar, leaderboard});

  auto main_renderer = Renderer(main_container, [&] {
    return hbox({
      sidebar_renderer->Render() | size(WIDTH, LESS_THAN, 20),
      separator(),
      leaderboard->Render() | flex,
    });
  });

  screen.Loop(main_renderer);
  return 0;
}

