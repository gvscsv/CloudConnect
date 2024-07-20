from flask import Flask, render_template
import pyrebase
import os

app = Flask(__name__)

# Firebase configuration
firebase_config = {
    "apiKey": "AIzaSyBhF7BusXZ0JPlAxMoE0tnV96uAJoJZTgM",
    "authDomain": "cloud-connect-2caee.firebaseapp.com",
    "databaseURL": "https://cloud-connect-2caee-default-rtdb.firebaseio.com",
    "storageBucket": "cloud-connect-2caee.appspot.com",
}

firebase = pyrebase.initialize_app(firebase_config)
db = firebase.database()

@app.route('/')
def index():
    try:
        button_state = db.child("buttonState").get().val()
        if button_state is not None:
            button_state = int(button_state)  # Ensure it's converted to an integer
        
        # Use relative paths within the static folder
        image_url = 'image1.jpg' if button_state == 1 else 'image2.jpeg'
        
        return render_template('index.html', image_url=image_url)
    except Exception as e:
        return f"Error: {e}"

if __name__ == '__main__':
    try:
        app.run(debug=True)
    except Exception as e:
        print(f"An error occurred: {e}")
