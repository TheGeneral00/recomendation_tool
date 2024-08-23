from kivy.app import App
from kivy.uix.label import Label
from kivy.graphics import Color, Rectangle
from kivy.uix.boxlayout import BoxLayout

class Root(BoxLayout):
    pass

class RecommendationToolApp(App):
    def build(self):
        return Root()
    
if __name__ == '__main__':
    RecommendationToolApp().run()
