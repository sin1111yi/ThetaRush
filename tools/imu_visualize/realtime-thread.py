import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from matplotlib.widgets import Slider
from matplotlib.gridspec import GridSpec
import time
from collections import deque
import threading
matplotlib.use('TkAgg')

class PyramidVisualizer:
    def __init__(self):
        # Initialize the main window
        self.fig = plt.figure(figsize=(16, 9))
        gs = GridSpec(6, 6, figure=self.fig)

        # 3D view
        self.ax3d = self.fig.add_subplot(gs[:, 3:6], projection="3d")

        # Waveform areas
        self.ax_realtime = self.fig.add_subplot(gs[0:2, 0:3])
        self.ax_history = self.fig.add_subplot(gs[3:5, 0:3])

        # Initialize parameters
        self._init_parameters()
        self._create_sliders()
        self._setup_data_thread()
        self._setup_timer()

        plt.subplots_adjust(
            left=0.05, right=0.95, bottom=0.15, top=0.9, hspace=1.2, wspace=0.8
        )

        self.update_plot()
        plt.show()

    def _init_parameters(self):
        """Initialize data storage and synchronization"""
        self.update_interval = 0.1
        self.start_time = time.time()
        self.data_lock = threading.Lock()

        self.angles = {"roll": 0, "pitch": 0, "yaw": 0}

        # Data storage with thread-safe access
        self.realtime_data = {
            "roll": deque(maxlen=100),
            "pitch": deque(maxlen=100),
            "yaw": deque(maxlen=100),
        }
        self.history_data = {
            "roll": deque(maxlen=3000),
            "pitch": deque(maxlen=3000),
            "yaw": deque(maxlen=3000),
            "time": deque(maxlen=3000),
        }

    def _create_sliders(self):
        slider_ax = [
            plt.axes([0.2, 0.15, 0.4, 0.03]),
            plt.axes([0.2, 0.1, 0.4, 0.03]),
            plt.axes([0.2, 0.05, 0.4, 0.03]),
        ]

        self.sliders = {
            "roll": Slider(slider_ax[0], "Roll", -180, 180, valinit=0),
            "pitch": Slider(slider_ax[1], "Pitch", -180, 180, valinit=0),
            "yaw": Slider(slider_ax[2], "Yaw", -180, 180, valinit=0),
        }

        for slider in self.sliders.values():
            slider.on_changed(self._on_slider_changed)

    def _setup_data_thread(self):
        """Create and start data update thread"""
        self.data_thread = threading.Thread(target=self._data_update_loop, daemon=True)
        self.data_thread.start()

    def _data_update_loop(self):
        """Background thread for data updates"""
        while True:
            start_time = time.time()
            current_time = time.time() - self.start_time

            # Get angles snapshot
            with self.data_lock:
                angles_snapshot = self.angles.copy()

            # Update data storage
            with self.data_lock:
                for key in angles_snapshot:
                    self.realtime_data[key].append((current_time, angles_snapshot[key]))
                self.history_data["time"].append(current_time)
                for key in angles_snapshot:
                    self.history_data[key].append(angles_snapshot[key])

            # Maintain update rate
            elapsed = time.time() - start_time
            sleep_time = max(0, self.update_interval - elapsed)
            time.sleep(sleep_time)

    def _setup_timer(self):
        """Set up the timer for GUI updates"""
        self.timer = self.fig.canvas.new_timer(int(self.update_interval * 1000))
        self.timer.add_callback(self._timed_update)
        self.timer.start()

    def _on_slider_changed(self, val):
        """Slider callback with thread-safe update"""
        with self.data_lock:
            self.angles = {name: s.val for name, s in self.sliders.items()}

    def _timed_update(self):
        """Main thread update callback"""
        self.update_plot()
        self.fig.canvas.draw_idle()

    def rotation_matrix(self):
        """Calculate rotation matrix with thread-safe access"""
        with self.data_lock:
            r = np.radians(self.angles["roll"])
            p = np.radians(self.angles["pitch"])
            y = np.radians(self.angles["yaw"])

        return np.array(
            [
                [
                    np.cos(y) * np.cos(p),
                    np.cos(y) * np.sin(p) * np.sin(r) - np.sin(y) * np.cos(r),
                    np.cos(y) * np.sin(p) * np.cos(r) + np.sin(y) * np.sin(r),
                ],
                [
                    np.sin(y) * np.cos(p),
                    np.sin(y) * np.sin(p) * np.sin(r) + np.cos(y) * np.cos(r),
                    np.sin(y) * np.sin(p) * np.cos(r) - np.cos(y) * np.sin(r),
                ],
                [-np.sin(p), np.cos(p) * np.sin(r), np.cos(p) * np.cos(r)],
            ]
        )

    def get_pyramid_vertices(self):
        base = np.array([[2, 0, 0], [0, 0, 1.5], [-1, 1, 0], [-1, -1, 0]])
        centroid = np.mean(base, axis=0)
        return (base - centroid).T

    def update_plot(self):
        """Update visualization elements"""
        self.ax3d.cla()
        self.ax_realtime.cla()
        self.ax_history.cla()

        # Get data copies for plotting
        with self.data_lock:
            realtime_copy = {k: list(v) for k, v in self.realtime_data.items()}
            history_copy = {k: list(v) for k, v in self.history_data.items()}
            current_time = time.time() - self.start_time

        self._update_3d_plot()
        self._plot_waveforms(current_time, realtime_copy, history_copy)

    def _update_3d_plot(self):
        """Update 3D visualization"""
        R = self.rotation_matrix()
        vertices = R @ self.get_pyramid_vertices()

        faces = [
            [vertices[:, 0], vertices[:, 1], vertices[:, 2]],
            [vertices[:, 1], vertices[:, 2], vertices[:, 3]],
            [vertices[:, 2], vertices[:, 0], vertices[:, 3]],
            [vertices[:, 0], vertices[:, 1], vertices[:, 3]],
        ]

        pyramid = Poly3DCollection(
            faces,
            facecolors=["#FF5733", "#33FF57", "#3357FF", "#FF33F5"],
            edgecolors="k",
            alpha=0.7,
            linewidths=1,
            shade=True,
        )
        self.ax3d.add_collection3d(pyramid)

        axis_vectors = R @ np.eye(3)
        for i, (color, label) in enumerate(zip(["r", "g", "b"], ["X", "Y", "Z"])):
            self.ax3d.quiver(
                0,
                0,
                0,
                axis_vectors[0, i],
                axis_vectors[1, i],
                axis_vectors[2, i],
                color=color,
                label=label,
                length=3.0,
                linewidth=3,
                arrow_length_ratio=0.15,
            )

        self.ax3d.legend(loc="upper left")
        self.ax3d.set_xlim(-4, 4)
        self.ax3d.set_ylim(-4, 4)
        self.ax3d.set_zlim(-4, 4)
        self.ax3d.view_init(elev=25, azim=45)
        self.ax3d.set_title("3D Pyramid Orientation", fontweight="bold", pad=20)
        self.ax3d.tick_params(
            axis="both",
            which="both",
            labelbottom=False,
            labelleft=False,
            labelright=False,
        )

    def _plot_waveforms(self, current_time, realtime_data, history_data):
        """Plot waveforms using copied data"""
        colors = {"roll": "#FF5733", "pitch": "#33FF57", "yaw": "#3357FF"}

        # Real-time plot
        for key in ["roll", "pitch", "yaw"]:
            if realtime_data[key]:
                times, values = zip(*realtime_data[key])
                self.ax_realtime.plot(times, values, label=key, color=colors[key])

        # Historical plot
        if history_data["time"]:
            for key in ["roll", "pitch", "yaw"]:
                self.ax_history.plot(
                    history_data["time"],
                    history_data[key],
                    label=key,
                    color=colors[key],
                )

        # Configure axes
        for ax, title, xmax in [
            (self.ax_realtime, "Real-time Angles (Last 10s)", current_time),
            (self.ax_history, "Historical Angles (Last 5min)", current_time),
        ]:
            ax.set_xlim(max(0, xmax - (10 if ax == self.ax_realtime else 300)), xmax)
            ax.set_ylim(-180, 180)
            ax.set_xlabel("Time (seconds)", fontweight="bold")
            ax.set_ylabel("Angle (degrees)", fontweight="bold")
            ax.set_title(title, fontweight="bold")
            ax.grid(True)
            ax.legend(loc="upper right")


if __name__ == "__main__":
    PyramidVisualizer()
