from kivy.app import App
from kivy.uix.label import Label
from kivy.graphics import Color, Rectangle
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.scrollview import ScrollView 
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.popup import Popup
from kivy.properties import DictProperty

import graph_module.graph_module

graph = graph_module.graph_module.graph

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


class Root(BoxLayout):
    entries = DictProperty([])

    def add_entry_popup(self):
        #create popup window
        content = BoxLayout(orientation='vertical')

        #TextInput for movie
        self.title_input = TextInput(hint_text='Enter the movie/show title')
        content.add_widget(self.title_input)

        #TextInput for genres
        self.genre_input = TextInput(hint_text='Enter genres (comma-separated)')
        content.add_widget(self.genre_input)

        #button to submit 
        submit_button = Button(text='Add entry', size_hint_y=None, height=40)
        submit_button.bind(on_press=self.add_entry)
        content.add_widget(submit_button)

        #Create and open the popup
        self.popup = Popup(title='Add new entry', content=content, size_hint=(0.8, 0.5))
        self.popup.open()

    def add_entry(self, instance):
        # Add a new entry to the list
        new_title = self.title_input.text
        raw_genres = self.genre_input.text

        if new_title and raw_genres:
            #Parse genres from comma-seperated input
            new_genres = [genre.strip() for genre in raw_genres.split(',')]
            self.entries[new_title] = new_genres
            self.update_entries()
            self.update_genres()
            self.popup.dismiss()

    def update_entries(self):
        # Clear existing widgets in the entries_layout
        self.ids.entries_layout.clear_widgets()

        # Add each entry as a new label
        for title, genres in self.entries.items():
            entry_label = Label(text=f"{title} - {', '.join(genres)}", size_hint_y=None, height=40)
            self.ids.entries_layout.add_widget(entry_label)

    def update_genres(self):
        genre_count = {}
        for genres in self.entries.values():
            for genre in genres:
                genre_count[genre] = genre_count.get(genre, 0) + 1

        top_genres = sorted(genre_count.items(), key=lambda x: x[1], reverse=True)[:5]
        self.ids.genres_box.clear_widgets()

        for genre, count in top_genres:
            genre_label = Label(text=f"{genre}: {count}", size_hint_y=None, height=40)
            self.ids.genres_box.add_widget(genre_label)

    def give_recommendation(self):
        print("Recommendations comming soon!")


class RecommendationToolApp(App):
    def build(self):
        return Root()
    
if __name__ == '__main__':
    RecommendationToolApp().run()
