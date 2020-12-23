# shellcheck disable=SC2164
cd /tmp
pm2 start pm2process.sh --name game-backend --log backend-logs