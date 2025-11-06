from setuptools import find_packages
from setuptools import setup

setup(
    name='latency_test_pkg',
    version='0.0.1',
    packages=find_packages(
        include=('latency_test_pkg', 'latency_test_pkg.*')),
)
