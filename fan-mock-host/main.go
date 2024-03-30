package main

import (
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
)

var speed int = 0

var allowOrigin string = "http://fan.home.pi"

func setupRouter() *gin.Engine {
	r := gin.Default()

	r.GET("/", func(c *gin.Context) {
		time.Sleep(time.Millisecond * 600)
		c.Writer.Header().Add("Access-Control-Allow-Origin", allowOrigin)
		c.JSON(http.StatusOK, gin.H{
			"success": true,
			"speed":   speed,
		})
	})

	r.POST("/", func(c *gin.Context) {
		time.Sleep(time.Millisecond * 600)
		var input Input
		c.Writer.Header().Add("Access-Control-Allow-Origin", allowOrigin)

		if c.Bind(&input) != nil {
			c.JSON(http.StatusBadRequest, gin.H{
				"success": false,
			})
			return
		}

		if input.Username != "yanoo" || input.Password != "samid" || input.Speed < 0 || input.Speed > 3 {
			c.JSON(http.StatusBadRequest, gin.H{
				"success": false,
			})
			return
		}

		speed = input.Speed
		c.JSON(http.StatusOK, gin.H{
			"success": true,
			"speed":   speed,
		})
	})

	return r
}

func main() {
	r := setupRouter()
	r.Run(":8000")
}

type Input struct {
	Username string `form:"username" binding:"required"`
	Password string `form:"password" binding:"required"`
	Speed    int    `form:"speed"`
}
