# python3


class Buffer:

    def __init__(self, size):
        self.size = size
        self.finish_time = []

    @property
    def is_full(self):
        """Return True if the buffer is full, False otherwise."""
        if len(self.finish_time) == self.size:
            return True
        return False

    @property
    def is_empty(self):
        """Return True if the buffer is empty, False otherwise."""
        if len(self.finish_time) == 0:
            return True
        return False

    @property
    def last_element(self):
        """Returns the last element of the buffer."""
        return self.finish_time[-1]

    def flush_processed(self, request):
        """
        Flushes processed elements of the buffer by the request's arrival time.
        """
        while self.finish_time:
            if self.finish_time[0] <= request.arrival_time:
                self.finish_time.pop(0)
            else:
                break

    def process(self, request):
        """Processes incoming request."""
        self.flush_processed(request)

        if self.is_full:
            return Response(True, -1)

        if self.is_empty:
            self.finish_time = [request.arrival_time + request.process_time]
            return Response(False, request.arrival_time)

        response = Response(False, self.last_element)
        self.finish_time.append(self.last_element + request.process_time)
        return response


class Request:
    """Incoming network packet."""

    def __init__(self, arrival_time, process_time):
        self.arrival_time = arrival_time
        self.process_time = process_time


class Response:
    """Response of the network buffer."""

    def __init__(self, dropped, start_time):
        self.dropped = dropped
        self.start_time = start_time


def read_requests(count):
    requests = []
    for i in range(count):
        arrival_time, process_time = map(int, input().strip().split())
        requests.append(Request(arrival_time, process_time))
    return requests


def process_requests(requests, buffer):
    return [buffer.process(r) for r in requests]


def print_responses(responses):
    for response in responses:
        print(response.start_time if not response.dropped else -1)


if __name__ == "__main__":
    size, count = map(int, input().strip().split())
    requests = read_requests(count)
    buffer = Buffer(size)
    responses = process_requests(requests, buffer)

    print_responses(responses)
