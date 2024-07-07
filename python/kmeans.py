import math
import sys

ERROR_MESSAGE = "An Error Has Occurred"


def k_means(K, input_data, iter="200"):
    if not validate_input_data(input_data):
        return
    vectors = file_to_vectors(input_data)
    if validate_K(K, len(vectors)):
        K = int(K)
    else:
        print("Invalid number of clusters!")
        return
    if validate_iter(iter):
        iter = int(iter)
    else:
        print("Invalid maximum iteration!")
        return

    centroids = compute_centroids(int(K), int(iter), vectors, 0.001)
    for centroid in centroids:
        print(",".join([round_four_digits(num) for num in centroid]))


def round_four_digits(num):
    # receive only floats
    num = round(num, 4)
    num = str(num)
    parts = num.split(".")
    if len(parts) != 2:
        print(ERROR_MESSAGE)
        return
    zeros = "0" * (4 - len(parts[1]))
    num = ".".join([parts[0], parts[1] + zeros])
    return num


def dist(v1, v2):
    sum = 0
    n = len(v1)
    for i in range(n):
        sum += pow(v1[i] - v2[i], 2)
    return math.sqrt(sum)


def compute_centroids(K, iter, vectors, epsilon):
    groups = {vectors[i]: [] for i in range(K)}
    for iteration in range(iter):
        changed = False
        for vector in vectors:
            centroid = min(groups.keys(), key=lambda x: dist(x, vector))
            groups[centroid].append(vector)
        new_groups = {}
        for centroid, group in groups.items():
            new_centroid = compute_new_centroid(group) if len(group) > 0 else centroid
            if dist(centroid, new_centroid) > epsilon:
                changed = True
            new_groups[new_centroid] = []
        if not changed:
            return groups.keys()
        groups = new_groups
    return groups.keys()


def file_to_vectors(input_data):
    vectors = []
    with open(input_data) as data:
        line = data.readline()
        while line != "" and line != "\n":
            vector = line[:-1].split(",")
            vector = [float(number) for number in vector]
            vectors.append(tuple(vector))
            line = data.readline()
    return vectors


def compute_new_centroid(group):
    d = len(group[0])
    new_centroid = [0 for j in range(d)]
    for i in range(d):
        for v in group:
            new_centroid[i] += v[i]
        new_centroid[i] = new_centroid[i] / len(group)
    return tuple(new_centroid)


def validate_K(K, N):
    return K.isnumeric() and N > int(K) > 1


def validate_iter(iter):
    return iter.isnumeric() and 1000 > int(iter) > 1


def validate_input_data(input_data):
    return input_data.endswith(".txt")


if __name__ == '__main__':
    if len(sys.argv) == 3:
        k_means(sys.argv[1], sys.argv[2])
    elif len(sys.argv) == 4:
        k_means(sys.argv[1], sys.argv[3], sys.argv[2])
    else:
        print(ERROR_MESSAGE)
