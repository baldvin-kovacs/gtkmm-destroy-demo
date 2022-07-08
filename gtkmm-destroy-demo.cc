#include <gtkmm.h>

#include <string>

class CustomWidget : public Gtk::Widget {
 public:
  CustomWidget(std::string name) : name{name} {
    button.set_label("foobar");
    button.set_parent(*this);
    signal_destroy().connect([this, name](){
      // This member will be taken for the managed instance.
      g_message("Unparenting %s from the Gtk::Widget destroy handler.", name.c_str());
      button.unparent();
    });
    set_layout_manager(Gtk::BinLayout::create());
  }
  ~CustomWidget() {
    if (button.get_parent()) {
      // This branch will be taken for the cw_as_member instance.
      g_message("Unparanting %s from destructor.", name.c_str());
      button.unparent();
    }
  }
 private:
  std::string name;
  Gtk::Button button;
};

class MainWindow : public Gtk::Window {
 public:
  MainWindow() : cw_as_member{"cw_as_member"} {
    box.append(cw_as_member);
    auto managed_cw = Gtk::make_managed<CustomWidget>("managed_cw");
    box.append(*managed_cw);
    set_child(box);
  }
 private:
  Gtk::Box box;
  CustomWidget cw_as_member;
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MainWindow>(argc, argv);
}
