require 'sinatra'
require_relative 'modules/Telegram.rb'

TELEGRAM_FEED = true

get '/' do
  "ITG2 machine alive"
  Telegram::send_message "ITG Server up"
end

post '/action' do 
  action = params['action']
  process_request(action)
  return ""
end


def process_request action 
  case action
  when 'coin'
    coin
  when 'service_coin'
    service_coin
  when 'crash'
    crash
  when 'poweron'
    poweron
  when 'song'
    playing_song
  else
    unknown action
  end
end



def coin
  puts "User coin"
  Telegram::send_message "User coin" if TELEGRAM_FEED
end

def service_coin
  puts "Service coin"
  Telegram::send_message "Service coin" if TELEGRAM_FEED
end

def crash
  puts "Game crashed"
  Telegram::send_message "Game crash" if TELEGRAM_FEED
end

def unknown type
  puts "Unknown event #{type}"
  Telegram::send_message "Unknown event #{type}" if TELEGRAM_FEED
end

def poweron
  puts "Game started"
  Telegram::send_message "Game started" if TELEGRAM_FEED
end

def playing_song
  puts "Playing song"
  Telegram::send_message "Playing song" if TELEGRAM_FEED
end
