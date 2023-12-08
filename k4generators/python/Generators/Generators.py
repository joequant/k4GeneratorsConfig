import Sherpa
import Whizard
import Madgraph

class Generators:
    """Generator class"""
    def __init__(self, generator_list):
        self.generator_list = generator_list
        self.sherpa = None
        self.whizard = None
        self.madgraph = None
        self.proc_info = None

    def set_process_info(self, proc_info):
        self.proc_info = proc_info

    def initialize_generators(self):
        if "Sherpa" in self.generator_list:
            if Sherpa is not None:
                self.sherpa = Sherpa.Sherpa(self.proc_info)
                self.sherpa.write_file()
            else:
                print("Sherpa module not found. Unable to initialize Sherpa.")
        if "Whizard" in self.generator_list:
            if Whizard is not None:
                self.whizard = Whizard.Whizard(self.proc_info)
                self.whizard.write_file()
            else:
                print("Whizard module not found. Unable to initialize Whizard.")

        if "Madgraph" in self.generator_list:
            if Madgraph is not None:
                self.madgraph = Madgraph.Madgraph(self.proc_info)
                self.madgraph.write_file()
            else:
                print("Madgraph module not found. Unable to initialize Madgraph.")