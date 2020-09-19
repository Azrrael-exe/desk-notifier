SHELL := /bin/bash

build-env:
	python3 -m venv venv;
	./venv/bin/pip install -r requirements.txt;

lauch-api:
	./venv/bin/python3 api/app.py;
