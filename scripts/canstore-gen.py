class Signal:
    def __init__(self, name, can_id, start_bit, end_bit, factor, offset):
        self.name = name
        self.can_id = can_id
        self.start_bit = start_bit
        self.end_bit = end_bit
        self.factor = factor
        self.offset = offset

    def to_case(self, index):
        case = []
        case.append("case 0x%X:" % self.can_id)
        case.append("\treal = blah")
        case.append("\tcanstore_set(canstore_data, %d, real)" % index)
        return '\n'.join(case)

class CanStoreGenerator:
    def __init__(self):
        self.signals = []

    def load(self, filename):
        input_file = file(filename, 'r')

        for line in input_file.readlines():
            data = line.strip().split(',')
            name = data[0]
            can_id = int(data[1], 16)
            start_bit = int(data[2])
            end_bit = int(data[3])
            factor = float(data[4])
            offset = float(data[5])

            new_signal = Signal(name, can_id, start_bit, end_bit, factor,
            offset)

            self.signals.append(new_signal)

    def generate(self):
        index = 0
        for sig in self.signals:
            print ("Index: %d CAN ID: 0x%X, Key: %s, Start bit: %d, End bit: %d, "
                   "Factor: %f, Offset: %f" % (index, sig.can_id, sig.name,
                   sig.start_bit, sig.end_bit, sig.factor, sig.offset))
            print sig.to_case(index)
            index = index + 1

if __name__ == '__main__':
    g = CanStoreGenerator()
    g.load('test.cfg')
    g.generate()
