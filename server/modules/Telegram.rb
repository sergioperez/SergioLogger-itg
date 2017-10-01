require 'net/http'
require 'uri'

#TODO: Replace @TOKEN and @SEND_TO
#TODO: It would be better to implement it reading them from a file

class Telegram 
  @TOKEN = "put_your_bot_token_here"
  @SEND_TO = "put_your_Telegram_user_here"

  def self.send_message(message)
    message = message.gsub!(" ","%20");
    puts "Telegram module: Sending #{message}"
    begin
      uri = URI.parse("https://api.telegram.org/bot#{@TOKEN}/sendMessage")
      uri.query = [uri.query, "chat_id=#{@SEND_TO}", "text=#{message}"].compact.join('&')
      res = Net::HTTP.get uri 
    rescue
      puts "Failed sending Telegram message"
    end
  end
end
