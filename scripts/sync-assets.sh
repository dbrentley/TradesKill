#!/usr/bin/env bash

/usr/bin/rclone copy \
  --create-empty-src-dirs \
  google-drive:tradeskill \
  /home/dbrent/workplace/TradesKill/assets
