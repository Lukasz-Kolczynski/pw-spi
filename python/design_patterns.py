class TV:
    def on(self):
        print("TV włączony")
    def off(self):
        print("TV wyłączony")

class BluRayPlayer:
    def on(self):
        print("Blu-Ray odtwarzacz włączony")
    def off(self):
        print("Blu-Ray odtwarzacz wyłączony")

class Speakers:
    def on(self):
        print("Głośniki włączone")
    def off(self):
        print("Głośniki wyłączone")

class Lights:
    def dim(self):
        print("Światła przyciemnione")
    def on(self):
        print("Światła włączone")


class HomeTheaterSystem:
    _instance = None 

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.tv = TV()
            cls._instance.player = BluRayPlayer()
            cls._instance.speakers = Speakers()
            cls._instance.lights = Lights()
        return cls._instance

    def watch_movie(self):
        print("=== Rozpoczynanie seansu ===")
        self.lights.dim()
        self.tv.on()
        self.speakers.on()
        self.player.on()

    def stop_movie(self):
        print("=== Kończenie seansu ===")
        self.player.off()
        self.speakers.off()
        self.tv.off()
        self.lights.on()


system = HomeTheaterSystem()

system.watch_movie()

print()

system.stop_movie()
