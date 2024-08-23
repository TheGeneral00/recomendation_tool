from kivy.app import App
from kivy.uix.label import Label
from kivy.graphics import Color, Rectangle
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.button import Button


class AutoSzieButton(Button):
    def on_size(self, args):
        super().on_size(*args)
        self._update_text_size()

    def _update_text_size(self):
        if self.text:
            #Reduce text size until text fits the button
            font_size = self.height/2
            while font_size > 5:
                self.font_size = font_size
                text_width = self.texture_size[0]
                text_height = self.texture_size[1]
                if text_width <= self.width and text_height <= self.height:
                    break
                font_size -= 1

class Root(FloatLayout):
    pass

class RecommendationToolApp(App):
    def build(self):
        return Root()
    
if __name__ == '__main__':
    RecommendationToolApp().run()
